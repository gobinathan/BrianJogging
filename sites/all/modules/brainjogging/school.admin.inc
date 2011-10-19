<?php

function bj_school_admin($args){
  
 
  switch($args){
    case 'list':
      return bj_learning_disability_list();
      break;
    case 'create':
      return  drupal_get_form('bj_school_create_form');
      break;
    case 'edit':
      return drupal_get_form('bj_school_create_form');
      break;
    case 'delete':
      return drupal_get_form('bj_school_delete_confirm');
      break;
    
  }
}

function bj_learning_disability_list(){
  $limit = 5;
  $sql_count = db_rewrite_sql("SELECT COUNT(sid) FROM {bj_school}");
  $school_res = pager_query("SELECT * FROM bj_school", $limit, 0, $sql_count);
  
  $header = array(
    array('data' => t('School')),
	  array('data' => t('Address')),
		t('Action')
  );
  
	while($school_object = db_fetch_object($school_res)) {
		$rows[] = array($school_object->school_name,
										$school_object->address,
                    l(t('Edit'), 'admin/brainjogging/school/edit/' . $school_object->sid) . '|'. l(t('Delete'), 'admin/brainjogging/school/delete/' . $school_object->sid),
                   );
	}
  
	if(!$rows) {
		$rows[] = array(
		  array(
		    'data'    => t('There are currently no Schools.'),
			  'colspan' => 3, 
			  'align'   => 'center'
			)
    );
	}
  
	$output = theme('table', $header, $rows);
  $output .= theme('pager', NULL, $limit, 0);
	return $output;
}


function bj_school_create_form(){
  
  $save = 'add';
  if(arg(3)=='edit' && arg(4)){
    $schol_obj = db_fetch_object(db_query("SELECT * FROM {bj_school} WHERE sid = ".arg(4)));
    $save = 'edit';
  }
  
  $form['school_name'] = array(
    '#type' => 'textfield',
    '#title' => t('School Name'),
    '#size' => 25,
    '#maxlength' => 30,
    '#default_value' => $schol_obj->school_name, 
    '#required' => TRUE,
    '#weight' => 0,
  );
   $form['phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone N0'),
    '#size' => 25,
    '#maxlength' => 30,
    '#default_value' => $schol_obj->phone, 
    '#required' => TRUE,
    '#weight' => 0,
  );
   $form['fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax No'),
    '#size' => 25,
    '#maxlength' => 30,
    '#default_value' => $schol_obj->fax, 
    '#required' => TRUE,
    '#weight' => 0,
  );
  $form['address'] = array(
    '#type' => 'textarea',
    '#title' => t('Address'),
    '#default_value' => $schol_obj->address, 
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



function bj_school_create_form_submit(&$form,&$form_state){
 
  if(($form_state['values']['submit'])=='add'){
   
    db_query("INSERT INTO {bj_school} (school_name,phone,fax,address) VALUES('".$form_state['values']['school_name']."','".$form_state['values']['phone']."','".$form_state['values']['fax']."','".$form_state['values']['address']."')");
    drupal_set_message(t('School Added successfuly'));
  }
   if(($form_state['values']['submit'])=='edit'){
    db_query("UPDATE {bj_school}  SET school_name='".$form_state['values']['school_name']."', phone='".$form_state['values']['phone']."', fax = '".$form_state['values']['fax']."', address = '".$form_state['values']['address']."'   WHERE sid=".arg(4));
     drupal_set_message(t('School Updated successfuly'));
  }
  
  $form_state['redirect'] = 'admin/brainjogging/school';
  return;
}

function bj_school_delete_confirm(){
  if(arg(3)=='delete' && arg(4)){
    $school_obj = db_fetch_object(db_query("SELECT * FROM {bj_school} WHERE sid = ".arg(4)));
  }
  
  $form = array();
  $form = array(
		'sid' => array(
			'#type' => 'value', 
			'#value' => $school_obj->sid,
		)
	);
  
  $output = confirm_form(
	  $form,
		t(
		  'Are you sure you want to delete this \'%title\' School?',
		  array('%title' => $school_obj->school_name)
    ),
    isset($_GET['destination']) ? $_GET['destination'] : "admin/brainjogging/school"
  );
  
	return $output;

}

function bj_school_delete_confirm_submit($form, &$form_state){
  
  if ($form_state['values']['confirm']) {
    if(isset($form_state['values']['sid'])) {
      db_query("DELETE FROM {bj_school} WHERE sid = ".$form_state['values']['sid']);
			drupal_set_message(t('The school has been deleted successfully.'));
  	}
  }
  $form_state['redirect'] = 'admin/brainjogging/school';
  return;
}