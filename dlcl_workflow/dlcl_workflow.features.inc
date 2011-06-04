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
      'rules_notify_node_author_of_comment' => array(
        '#type' => 'rule',
        '#set' => 'event_comment_insert',
        '#label' => 'Email author when a Comment is posted',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'workflow',
          'dlcl_workflow' => 'dlcl_workflow',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '1' => array(
            '#weight' => 0,
            '#type' => 'condition',
            '#settings' => array(
              '#argument map' => array(
                'user1' => 'comment_author',
                'user2' => 'node_author',
              ),
            ),
            '#name' => 'rules_condition_user_comparison',
            '#negate' => 1,
            '#info' => array(
              'label' => 'Compare 2 users (do not notif if one comments own node)',
              'label callback' => FALSE,
              'arguments' => array(
                'user1' => array(
                  'type' => 'user',
                  'label' => 'Benutzerkonto 1',
                ),
                'user2' => array(
                  'type' => 'user',
                  'label' => 'Benutzerkonto 2',
                ),
              ),
              'module' => 'User',
            ),
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'E-Mail the node author',
              'label callback' => FALSE,
              'module' => 'System',
              'eval input' => array(
                '0' => 'subject',
                '1' => 'message',
                '2' => 'from',
                '3' => 'to',
              ),
            ),
            '#name' => 'rules_action_mail',
            '#settings' => array(
              'to' => '[node_author:mail]',
              'from' => '',
              'subject' => 'New Comment',
              'message' => 'New comment from [comment_author:user] for [node:type] [node:title]',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'message' => array(
                    '0' => 'comment_author',
                    '1' => 'node',
                  ),
                  'to' => array(
                    '0' => 'node_author',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_notify_publicist_new_news_or_event' => array(
        '#type' => 'rule',
        '#altered' => TRUE,
        '#categories' => array(
          '0' => 'workflow',
          'dlcl_workflow' => 'dlcl_workflow',
        ),
        '#label' => 'Notify publicist on news or event creation',
        '#set' => 'event_node_presave',
        '#status' => 'default',
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'to' => 'dianejak@stanford.edu',
              'from' => '',
              'subject' => '[node_unchanged:title] has been modified!',
              'message' => 'Hello!

A [node_unchanged:type-name] with the title [node_unchanged:title] has been created by [user:user] on [node:site-date]:
[node:site-url]/node/[node_unchanged:nid] for your administrative approval or editorial discretion.

The DLCL site robot.',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'subject' => array(
                    '0' => 'node_unchanged',
                  ),
                  'message' => array(
                    '0' => 'node',
                    '1' => 'node_unchanged',
                    '2' => 'user',
                  ),
                ),
              ),
            ),
            '#name' => 'rules_action_mail',
            '#info' => array(
              'label' => 'Send a mail to Diane',
              'label callback' => FALSE,
              'module' => 'System',
              'eval input' => array(
                '0' => 'subject',
                '1' => 'message',
                '2' => 'from',
                '3' => 'to',
              ),
            ),
          ),
        ),
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'event' => 'event',
                'news' => 'news',
              ),
              '#argument map' => array(
                'node' => 'node_unchanged',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Unchanged content is Event or News Item',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => -3,
          ),
          '1' => array(
            '#info' => array(
              'label' => 'Unchanged content is new',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_new',
            '#settings' => array(
              '#argument map' => array(
                'node' => 'node_unchanged',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
        ),
        '#active' => 1,
        '#weight' => '0',
        '#version' => 6003,
      ),
      'rules_workflow_owner_asssinment' => array(
        '#type' => 'rule',
        '#set' => 'event_node_presave',
        '#label' => 'Email users when they are made Content Owner of a News item',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'workflow',
          'dlcl_workflow' => 'dlcl_workflow',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'news' => 'news',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
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
          ),
          '1' => array(
            '#weight' => 0,
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
            '#name' => 'content_rules_field_changed',
            '#settings' => array(
              'field_name' => 'field_workflow_owner',
              '#argument map' => array(
                'node' => 'node',
                'node_unchanged' => 'node_unchanged',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#info' => array(
              'label' => 'Load the user referenced by the Content Owner field',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content containing the user reference field',
                ),
              ),
              'new variables' => array(
                'referenced_user' => array(
                  'label' => 'content owner',
                  'label callback' => FALSE,
                  'type' => 'user',
                ),
              ),
              'module' => 'CCK',
            ),
            '#name' => 'userreference_rules_action_load',
            '#settings' => array(
              'field' => 'field_workflow_owner',
              '#argument map' => array(
                'node' => 'node',
                'referenced_user' => 'referenced_user',
              ),
            ),
            '#type' => 'action',
            '#weight' => 0,
          ),
          '1' => array(
            '#weight' => 7,
            '#type' => 'action',
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
            '#name' => 'rules_action_mail_to_user',
            '#info' => array(
              'label' => 'Send an email to the content owner',
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
