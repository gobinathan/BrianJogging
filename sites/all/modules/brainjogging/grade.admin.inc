<?php

function bj_grade_admin($args){
  switch($args){
    case 'list':
      bj_grade_list();
      break;
    case 'create':
      $output = drupal_get_form('bj_grade_create_form');
      break;
    case 'edit':
      $output = drupal_get_form('bj_grade_create_form');
      break;
    case 'delete':
      bj_greade_delete();
      break;
  }
}

function bj_grade_list(){
  echo "List view comes here";
  //TODO
  //Create listview of user grades from bj_grades table
}

function bj_grade_create_form(){
  //TODO
  //Create form to add user grades 
}

function bj_grade_create_form_validate(){
  //TODO
  //Validator for bj_grade_create_form
}

function bj_grade_create_form_submit(){
  //TODO
  //submit function for bj_grade_create_form
}

function bj_greade_delete(){
  //TODO
  //Delete a grade
}