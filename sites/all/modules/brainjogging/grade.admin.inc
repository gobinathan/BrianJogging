<?php

function bj_grade_admin($args){
  
  switch($args){
    case 'list':
      bj_grade_list();
      break;
    case 'create':
      return  drupal_get_form('bj_grade_create_form');
      break;
    case 'edit':
      return drupal_get_form('bj_grade_create_form');
      break;
    case 'delete':
      bj_greade_delete();
      break;
    
  }
}

function bj_grade_list(){
  
  echo "List view comes here";
   $res=mysql_query("select * from bj_grade");
   $grades=array();
   while($grade=mysql_fetch_array($res))
   {
    array_push($grades,$grade);
   }
  
  foreach($grades as $key=>$grade)
  {
    $key+=1;
    echo "<br>".$key."&nbsp;".$grade['name']."&nbsp;".$grade['description']."<a href=/admin/brainjogging/grade/edit/".$grade['gid'].">Edit</a>";
    
    
    
  }
  
  
  
}

function bj_grade_create_form(){
  
  if(arg(3)=='edit' && arg(4)){
  $grade_obj = db_fetch_object(db_query("SELECT * FROM {bj_grade} WHERE gid = ".arg(4)));
  }
  
  $form['Name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#size' => 25,
    '#maxlength' => 30,
    '#default_value' => $grade_obj->name, 
    '#required' => TRUE,
    '#weight' => 0,
  );
  $form['Description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#required' => TRUE,
    '#default_value' => $grade_obj->description, 
    '#weight' => 15,
  );
    $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Save'),
    '#value'=>t('Save'),
    '#weight' => 16,
  );
    
    
    
  return $form;
}

function bj_grade_create_form_validate(){
  //TODO
  //Validator for bj_grade_create_form
 
}

function bj_grade_create_form_submit(){

  $res=mysql_query("INSERT INTO bj_grade VALUES('','$_POST[Name]','$_POST[Description]')");
  if($res){
    drupal_set_message(t('Your form has been saved.'));
  }
  else{
    echo mysql_error();
  }
 
}

function bj_greade_delete(){
  //TODO
  //Delete a grade
}