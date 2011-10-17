<?php

function brainjogging_site_settings_manage() {
	
  $form['lf']['missed_letters'] = array(
    '#type' => 'textfield',
    '#title' => t('No of missed letters taken for reinforcement'),
    '#default_value' => variable_get('missed_letters','5')
  );
	$form['lf']['missed_letters_reinforcement'] = array(
    '#type' => 'textfield',
    '#title' => t('Missed letters reinforcement percentage'),
		'#description' => ('THis should be in percentage (1-100%)'),
    '#default_value' => variable_get('missed_letters_reinforcement',"50")
  );
	$form['lf']['start_from_same_level_per'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the percentage to allow the user to start from the same level'),
		'#description' => ('THis should be in percentage (1-100%)'),
    '#default_value' => variable_get('start_from_same_level_per',"50")
  );
  return system_settings_form($form);
}