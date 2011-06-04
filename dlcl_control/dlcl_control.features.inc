<?php

/**
 * Implementation of hook_rules_defaults().
 */
function dlcl_control_rules_defaults() {
  return array(
    'rules' => array(
      'rules_redirect_editors_to_control_panel_on_login' => array(
        '#type' => 'rule',
        '#set' => 'event_user_login',
        '#label' => 'Redirect editors to the control panel on login',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'control panel',
          'dlcl_control' => 'dlcl_control',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'roles' => array(
                '0' => 9,
                '1' => 17,
                '2' => 5,
                '3' => 7,
              ),
              'operation' => 'OR',
              '#argument map' => array(
                'user' => 'account',
              ),
            ),
            '#name' => 'rules_condition_user_hasrole',
            '#info' => array(
              'label' => 'User has role(s)',
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'User',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'redirect to control panel',
              'label callback' => FALSE,
              'module' => 'System',
              'eval input' => array(
                '0' => 'path',
                '1' => 'query',
                '2' => 'fragment',
              ),
            ),
            '#name' => 'rules_action_drupal_goto',
            '#settings' => array(
              'path' => 'admin/control',
              'query' => '',
              'fragment' => '',
              'force' => 1,
              'immediate' => 0,
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function dlcl_control_views_api() {
  return array(
    'api' => '2',
  );
}
