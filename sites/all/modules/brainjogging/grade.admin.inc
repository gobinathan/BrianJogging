<?php

function bj_grade_admin($args){
  
  switch($args){
    case 'list':
      return bj_grade_list();
      break;
    case 'create':
      return  drupal_get_form('bj_grade_create_form');
      break;
    case 'edit':
      return drupal_get_form('bj_grade_create_form');
      break;
    case 'delete':
      return drupal_get_form('bj_greade_delete_confirm');
      break;
    
  }
}

function bj_grade_list(){
  $limit = 5;
  $sql_count = db_rewrite_sql("SELECT COUNT(gid) FROM {bj_grade}");
  $grade_res = pager_query("SELECT * FROM bj_grade", $limit, 0, $sql_count);
  
  $header = array(
    array('data' => t('Grade')),
	  array('data' => t('Description')),
		t('Action')
  );
  
	while($grade_object = db_fetch_object($grade_res)) {
		$rows[] = array($grade_object->name,
										$grade_object->description,
                    l(t('Edit'), 'admin/brainjogging/grade/edit/' . $grade_object->gid) . '|'. l(t('Delete'), 'admin/brainjogging/grade/delete/' . $grade_object->gid),
                   );
	}
  
	if(!$rows) {
		$rows[] = array(
		  array(
		    'data'    => t('There are currently no grades.'),
			  'colspan' => 3, 
			  'align'   => 'center'
			)
    );
	}
  
	$output = theme('table', $header, $rows);
  $output .= theme('pager', NULL, $limit, 0);
	return $output;
}

function bj_grade_create_form(){
  
  $save = 'add';
  if(arg(3)=='edit' && arg(4)){
    $grade_obj = db_fetch_object(db_query("SELECT * FROM {bj_grade} WHERE gid = ".arg(4)));
    $save = 'edit';
  }
  
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#size' => 25,
    '#maxlength' => 30,
    '#default_value' => $grade_obj->name, 
    '#required' => TRUE,
    '#weight' => 0,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $grade_obj->description, 
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



function bj_grade_create_form_submit(&$form,&$form_state){
  if(($form_state['values']['submit'])=='save'){
    db_query("INSERT INTO {bj_grade} (name,description) VALUES('".$form_state['values']['name']."','".$form_state['values']['description']."')");
  }
   if(($form_state['values']['submit'])=='edit'){
    db_query("UPDATE {bj_grade}  SET name='".$form_state['values']['name']."', description='".$form_state['values']['description']."' WHERE gid=".arg(4));
  }
  drupal_set_message(t('Grade added successfuly'));
  $form_state['redirect'] = 'admin/brainjogging/grade';
  return;
}

function bj_greade_delete_confirm(){
  if(arg(3)=='delete' && arg(4)){
    $grade_obj = db_fetch_object(db_query("SELECT * FROM {bj_grade} WHERE gid = ".arg(4)));
  }
  
  $form = array();
  $form = array(
		'gid' => array(
			'#type' => 'value', 
			'#value' => $grade_obj->gid,
		)
	);
  
  $output = confirm_form(
	  $form,
		t(
		  'Are you sure you want to delete this \'%title\' grade?',
		  array('%title' => $grade_obj->name)
    ),
    isset($_GET['destination']) ? $_GET['destination'] : "admin/brainjogging/grade"
  );
  
	return $output;

}

function bj_greade_delete_confirm_submit($form, &$form_state){
  if ($form_state['values']['confirm']) {
    if(isset($form_state['values']['gid'])) {
      db_query("DELETE FROM {bj_grade} WHERE gid = ".$form_state['values']['gid']);
			drupal_set_message(t('The grade has been deleted successfully.'));
  	}
  }
  $form_state['redirect'] = 'admin/brainjogging/grade';
  return;
}