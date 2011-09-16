<?php

function bj_grade_admin($args){
  switch($args){
    case 'list':
      bj_grade_list();
      break;
    case 'create':
      bj_greade_create();
      break;
    case 'edit':
      bj_greade_create();
      break;
    case 'delete':
      bj_greade_delete();
      break;
  }
}

function bj_grade_list(){
  //TODO
  //Create listview of user grades from bj_grades table
}

function bj_greade_create(){
  //TODO
  //Create form to add user grades and insert the form values into bj_grades table
  //the same form also used to edit the grade values
}

function bj_greade_delete(){
  //TODO
  //Delete a grade
}