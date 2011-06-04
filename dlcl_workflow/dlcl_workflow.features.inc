<?php

/**
 * Implementation of hook_rules_defaults().
 */
function dlcl_workflow_rules_defaults() {
  return array(
    'rules' => array(
      'rules_notify_author_of_node_edit' => array(
        '#type' => 'rule',
        '#altered' => TRUE,
        '#categories' => array(
          '0' => 'workflow',
          'dlcl_workflow' => 'dlcl_workflow',
        ),
        '#label' => 'Notify the content author about changes from other users',
        '#set' => 'event_node_update',
        '#status' => 'default',
        '#actions' => array(
          '1' => array(
            '#name' => 'rules_action_mail_to_user',
            '#type' => 'action',
            '#settings' => array(
              '#argument map' => array(
                'author' => 'user',
              ),
              'from' => '',
              'subject' => '[node_unchanged:title] has been modified!',
              'message' => 'Hello [author_unchanged:user]!

Your [node_unchanged:type-name] with the title [node_unchanged:title] has been modified by [user:user] at [node:site-date]:
[node:site-url]/node/[node_unchanged:nid].

--- [node:site-name]',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'subject' => array(
                    '0' => 'node_unchanged',
                  ),
                  'message' => array(
                    '0' => 'node',
                    '1' => 'node_unchanged',
                    '2' => 'author_unchanged',
                    '3' => 'user',
                  ),
                ),
              ),
            ),
            '#label' => 'Inform the author by mail',
            '#weight' => 0,
            '#info' => array(
              'label' => 'Inform the author by mail',
              'label callback' => FALSE,
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'Recipient',
                ),
              ),
              'module' => 'System',
              'eval input' => array(
                '0' => 'subject',
                '1' => 'message',
                '2' => 'from',
              ),
            ),
          ),
        ),
        '#conditions' => array(
          '0' => array(
            '#negate' => 1,
            '#name' => 'rules_condition_user_comparison',
            '#type' => 'condition',
            '#label' => 'updating user is author',
            '#settings' => array(
              '#argument map' => array(
                'author' => 'user1',
                'user' => 'user2',
              ),
            ),
            '#weight' => 0,
            '#info' => array(
              'label' => 'Compare two users',
              'arguments' => array(
                'user1' => array(
                  'type' => 'user',
                  'label' => 'User account 1',
                ),
                'user2' => array(
                  'type' => 'user',
                  'label' => 'User account 2',
                ),
              ),
              'help' => 'Evaluates to TRUE, if both given user accounts are the same.',
              'module' => 'User',
            ),
          ),
        ),
        '#active' => 1,
        '#weight' => '0',
        '#version' => 6003,
      ),
      'rules_workflow_owner_asssinment' => array(
        '#type' => 'rule',
        '#set' => 'event_node_presave',
        '#label' => 'workflow owner asssinment',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'workflow',
          'dlcl_workflow' => 'dlcl_workflow',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Saved content is News Item',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'news' => 'news',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
          '1' => array(
            '#type' => 'condition',
            '#settings' => array(
              'field_name' => 'field_workflow_owner',
              '#argument map' => array(
                'node' => 'node',
                'node_unchanged' => 'node_unchanged',
              ),
            ),
            '#name' => 'content_rules_field_changed',
            '#info' => array(
              'label' => 'Workflow owner has changed',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content containing changes',
                ),
                'node_unchanged' => array(
                  'type' => 'node',
                  'label' => 'Content not containing changes',
                ),
              ),
              'module' => 'CCK',
            ),
            '#weight' => 0,
          ),
          '2' => array(
            '#type' => 'OR',
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              'field' => 'field_workflow_owner',
              '#argument map' => array(
                'node' => 'node',
                'referenced_user' => 'referenced_user',
              ),
            ),
            '#name' => 'userreference_rules_action_load',
            '#info' => array(
              'label' => 'Load a referenced user',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content containing the user reference field',
                ),
              ),
              'new variables' => array(
                'referenced_user' => array(
                  'type' => 'user',
                  'label' => 'Referenced user',
                ),
              ),
              'module' => 'CCK',
            ),
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Send a mail to a user',
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'Recipient',
                ),
              ),
              'module' => 'System',
              'eval input' => array(
                '0' => 'subject',
                '1' => 'message',
                '2' => 'from',
              ),
            ),
            '#name' => 'rules_action_mail_to_user',
            '#settings' => array(
              'from' => '',
              'subject' => '[dlcl editorial workflow] You have been assigned new content nid:[node_unchanged:nid]',
              'message' => 'The [node_unchanged:type]
[node_unchanged:title]
by [author:user-raw]

has been assigned to you.

View this content at [node_unchanged:node-url]
',
              '#argument map' => array(
                'user' => 'referenced_user',
              ),
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'subject' => array(
                    '0' => 'node_unchanged',
                  ),
                  'message' => array(
                    '0' => 'author',
                    '1' => 'node_unchanged',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
    'rule_sets' => array(
      'rules_dlcl_editorial_workflow' => array(
        'arguments' => array(),
        'label' => 'DLCL editorial workflow',
        'status' => 'default',
        'categories' => array(
          '0' => 'workflow',
          'dlcl_workflow' => 'dlcl_workflow',
        ),
      ),
    ),
  );
}
