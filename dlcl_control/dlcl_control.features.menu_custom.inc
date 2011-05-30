<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function dlcl_control_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-control
  $menus['menu-control'] = array(
    'menu_name' => 'menu-control',
    'title' => 'control',
    'description' => 'the control panel administrative menu.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('control');
  t('the control panel administrative menu.');


  return $menus;
}
