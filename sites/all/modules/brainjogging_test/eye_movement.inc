<?php

function eye_movement_submit($args){
  global $user;
  $date = date('Y-m-d H:i:s');
  $rese   = $_POST["res"];
  $result = json_decode($rese);
  $wl_id=array();
  foreach($result as $key => $res){
   echo hai;
   db_query("INSERT INTO bj_eyemovement_test VALUES('','".$user->uid."','','".$res[$key]."','$date','','".$user->sid."')");
  }
 }


