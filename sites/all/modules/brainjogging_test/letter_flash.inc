<?php

function letter_flash_submit($args){
 $date = date('Y-m-d H:i:s');
 $rese   = $_POST["res"];
  $result = json_decode($rese);
  $arr = array();
  $i = 1 ;
  foreach($result as $res)
  {
    $j = 1;
    foreach($res as $r){
      $arr[$i][$j] = (array)$r;
      $j++;
    }
    $i++;
  }

 $my_res=db_query("INSERT INTO bj_letterflash_test VALUES('','','','$date',".$arr[4][1][0].",".$arr[4][2][0].",".$arr[4][3][0].",".$arr[4][4][0].",".$arr[4][2][0].")");
 if($my_res){ 
  $id=mysql_insert_id();
  $f_count=count($arr[3][3]);
  for($c=1;$c<$f_count;$c++){
 
  db_query("INSERT INTO bj_letterflash_test_missed_letters VALUES('$id','','".$arr[3][1][$c]."','".$arr[3][2][$c]."','".$arr[3][5][$c]."','".$arr[3][3][$c]."','".$arr[3][4][$c]."')");

   }
 }
 


  
}


