<?php

/**
 * @file
 * Rules integration for the Send View module.
 */

/**
 * Implements hook_rules_action_info().
 */
function send_view_rules_action_info() {
  return array(
    'send_view_action' => array(
      'label' => t('Send a view'),
      'group' => t('Views'),
      'parameter' => array(
        'method' => array(
          'label' => t('Send via'),
          'type' => 'text',
          'options list' => 'send_view_action_method_options_list',
          'restriction' => 'input',
        ),
        'destination' => array(
          'label' => t('Destination'),
          'type' => 'text',
          'description' => t('e.g., the phone number or email address to which this view should be sent'),
        ),
        'view' => array(
          'label' => t('View/display'),
          'type' => 'text',
          'options list' => 'send_view_action_view_options_list',
        ),
        'arguments' => array(
          'label' => t('View arguments'),
          'type' => 'text',
          'description' => t('e.g., "arg1/arg2"'),
        ),
      ),
    ),
  );
}

function send_view_action_method_options_list() {
  $options = array();
  foreach (send_view_get_methods() as $method_name => $method) {
    $options[$method_name] = $method['label'];
  }
  return $options;
}

function send_view_action_view_options_list() {
  $views = views_get_all_views();
  $options = array();
  foreach ($views as $view) {
    foreach ($view->display as $display) {
      $options["$view->name|$display->id"] = "$view->human_name: $display->display_title";
    }
  }

  asort($options);
  return $options;
}

function send_view_action($method, $destination, $view, $args) {
  $view = explode('|', $view);
  send_view($method, $destination, $view[0], $view[1], $args);
}
