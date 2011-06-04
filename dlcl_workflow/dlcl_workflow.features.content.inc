<?php

/**
 * Implementation of hook_content_default_fields().
 */
function dlcl_workflow_content_default_fields() {
  $fields = array();

  // Exported field: field_workflow_owner
  $fields['news-field_workflow_owner'] = array(
    'field_name' => 'field_workflow_owner',
    'type_name' => 'news',
    'display_settings' => array(
      'weight' => '16',
      'parent' => 'group_workflow',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'userreference',
    'required' => '0',
    'multiple' => '2',
    'module' => 'userreference',
    'active' => '1',
    'referenceable_roles' => array(
      '5' => 5,
      '7' => 7,
      '2' => 0,
      '21' => 0,
      '15' => 0,
      '23' => 0,
      '9' => 0,
      '17' => 0,
      '11' => 0,
      '3' => 0,
      '19' => 0,
    ),
    'referenceable_status' => '1',
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'widget' => array(
      'autocomplete_match' => 'contains',
      'size' => 60,
      'reverse_link' => 0,
      'default_value' => array(
        '0' => array(
          'uid' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'content owner',
      'weight' => '16',
      'description' => '',
      'type' => 'userreference_buttons',
      'module' => 'userreference',
    ),
  );

  // Exported field: field_workflow_state
  $fields['news-field_workflow_state'] = array(
    'field_name' => 'field_workflow_state',
    'type_name' => 'news',
    'display_settings' => array(
      'weight' => '15',
      'parent' => 'group_workflow',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 1,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'draft|draft
edit|edit
published|published
',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'workflow state',
      'weight' => '15',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('content owner');
  t('workflow state');

  return $fields;
}
