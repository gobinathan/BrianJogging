<?php 
function eye_movement_submit($args){
  global $user;
  
  $date = date('Y-m-d H:i:s');
  $rese   = $_POST["res"];
  $speed  = $_POST["speed"];
  
  $tid= db_result(db_query("SELECT tid  FROM {bj_user_teachers} WHERE uid = '%d'", $user -> uid));
  $teacher=user_load($tid);
  $teacher_id  = $teacher->uid;
 
  
  
  
  
  
  $result = json_decode($rese);
  

  $wl_id=array();
  if(in_array('independent client',$user->roles) || in_array('dependent client',$user->roles)){
  foreach($result as $key => $res){
  
   db_query("INSERT INTO bj_eyemovement_test VALUES('','".$user->uid."','$teacher_id','".$res[$key]."','$date','$speed','".$user->sid."')");
  }
 
  
  
  }
 }


