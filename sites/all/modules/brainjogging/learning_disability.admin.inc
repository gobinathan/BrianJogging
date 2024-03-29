<?php

function bj_learning_disability_admin($args){
  
  switch($args){
    case 'list':
      return bj_learning_disability_list();
      break;
    case 'create':
      return  drupal_get_form('bj_learning_disability_create_form');
      break;
    case 'edit':
      return drupal_get_form('bj_learning_disability_create_form');
      break;
    case 'delete':
      return drupal_get_form('bj_learning_disability_delete_confirm');
      break;
    
  }
}

function bj_learning_disability_list(){
  $limit = 5;
  $sql_count = db_rewrite_sql("SELECT COUNT(did) FROM {bj_learning_disability}");
  $learning_disability_res = pager_query("SELECT * FROM bj_learning_disability", $limit, 0, $sql_count);
  
  $header = array(
    array('data' => t('Learning Disability')),
	  array('data' => t('Description')),
		t('Action')
  );
  
	while($learning_disability_object = db_fetch_object($learning_disability_res)) {
		$rows[] = array($learning_disability_object->name,
										$learning_disability_object->description,
                    l(t('Edit'), 'admin/brainjogging/learning_disability/edit/' . $learning_disability_object->did, array('attributes'=> array('class' => 'icon edit'))) . l(t('Delete'), 'admin/brainjogging/learning_disability/delete/' . $learning_disability_object->did,array('attributes'=> array('class' => 'icon delete'))),
                   );
	}
  
	if(!$rows) {
		$rows[] = array(
		  array(
		    'data'    => t('There are currently no Learning Disability.'),
			  'colspan' => 3, 
			  'align'   => 'center'
			)
    );
	}
  
	$output = theme('table', $header, $rows);
  $output .= theme('pager', NULL, $limit, 0);
	return $output;
}

function bj_learning_disability_create_form(){
  
  $save = 'add';
  if(arg(3)=='edit' && arg(4)){
    $learning_disability_obj = db_fetch_object(db_query("SELECT * FROM {bj_learning_disability} WHERE did = ".arg(4)));
    $save = 'edit';
  }
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#size' => 25,
    '#maxlength' => 30,
    '#default_value' => $learning_disability_obj->name, 
    '#required' => TRUE,
    '#weight' => 0,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $learning_disability_obj->description, 
    '#weight' => 1,
  );
	$form['letter_flash_select_case'] = array(
    '#type' => 'radios',
    '#title' => t('Have select case option in letter flash'),
		'#options' => array(t('Disabled'), t('Enabled')),
    '#default_value' => $learning_disability_obj->letter_flash_select_case, 
    '#weight' => 1,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Save'),
    '#value'=> $save,
    '#weight' => 2,
  );
    
  return $form;
}

function bj_grade_create_form_validate(){
  //TODO
  //Validator for bj_grade_create_form
 
}



function bj_learning_disability_create_form_submit(&$form,&$form_state){
 
  if(($form_state['values']['submit'])=='add'){
   
    db_query("INSERT INTO {bj_learning_disability} (name,description,letter_flash_select_case) VALUES('".$form_state['values']['name']."','".$form_state['values']['description']."',".$form_state['values']['letter_flash_select_case'].")");
    drupal_set_message(t('Learning Disability Added successfuly'));
  }
   if(($form_state['values']['submit'])=='edit'){
    db_query("UPDATE {bj_learning_disability}  SET name='".$form_state['values']['name']."', description='".$form_state['values']['description']."', letter_flash_select_case = ".$form_state['values']['letter_flash_select_case']."  WHERE did=".arg(4));
     drupal_set_message(t('Learning Disability Updated successfuly'));
  }
  
  $form_state['redirect'] = 'admin/brainjogging/learning_disability';
  return;
}

function bj_learning_disability_delete_confirm(){
  if(arg(3)=='delete' && arg(4)){
    $learning_disability_obj = db_fetch_object(db_query("SELECT * FROM {bj_learning_disability} WHERE did = ".arg(4)));
  }
  
  $form = array();
  $form = array(
		'did' => array(
			'#type' => 'value', 
			'#value' => $learning_disability_obj->did,
		)
	);
  
  $output = confirm_form(
	  $form,
		t(
		  'Are you sure you want to delete this \'%title\' Learning Disability?',
		  array('%title' => $learning_disability_obj->name)
    ),
    isset($_GET['destination']) ? $_GET['destination'] : "admin/brainjogging/learning_disability"
  );
  
	return $output;

}

function bj_learning_disability_delete_confirm_submit($form, &$form_state){
  
  if ($form_state['values']['confirm']) {
    if(isset($form_state['values']['did'])) {
      db_query("DELETE FROM {bj_learning_disability} WHERE did = ".$form_state['values']['did']);
			drupal_set_message(t('The learning disability has been deleted successfully.'));
  	}
  }
  $form_state['redirect'] = 'admin/brainjogging/learning_disability';
  return;
}