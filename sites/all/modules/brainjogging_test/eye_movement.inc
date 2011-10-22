<?php 
function eye_movement_submit($args){
  global $user;
  $date = date('Y-m-d H:i:s');
  $rese   = $_POST["res"];
  $result = json_decode($rese);
  $wl_id=array();
  if(in_array('independent client',$user->roles) || in_array('dependent client',$user->roles)){
  foreach($result as $key => $res){
   db_query("INSERT INTO bj_eyemovement_test VALUES('','".$user->uid."','','".$res[$key]."','$date','','".$user->sid."')");
  }
  echo session_id();
  
  
  }
 }


