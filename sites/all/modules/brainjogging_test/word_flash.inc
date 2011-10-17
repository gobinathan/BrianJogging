<?php

function word_flash_submit($args){
 $date = date('Y-m-d H:i:s');
 $rese   = $_POST["res"];
 
 //$var='{"status":{"wrong":4,"correct":0},"levels":[null,{"question":"Apple Apricot","answer":"jkflfkj","result":0,"level":1,"attempt":1},{"question":"Apple Apricot","answer":"adkfjk","result":0,"level":1,"attempt":2},{"question":"Apple Apricot","answer":"fjjllad","result":0,"level":1,"attempt":3},{"question":"Apple Apricot","answer":"fklfdkjjk","result":0,"level":1,"attempt":4}],"res":{"res":{"attempts":4,"level":1,"ftype":"2","ftype_text":" Two Words Flash ","wordlist":"1","fsize":"medium"}},"pers":{"perecent":0},"tot_atem":{"tot":4}}';
 
 
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
 
 $arr[3][1]['attempts']+$arr[1][2][0];
 $my_res=db_query("INSERT INTO bj_wordflash_test VALUES('','','','$date',".$arr[5][1][0].",".$arr[1][2][0].",".$arr[4][1][0].",".$arr[3][1]['level'].",".$arr[3][1]['ftype'].")");
 if($my_res){ 
  $id=mysql_insert_id();
  $f_count=count($arr[2]);
  for($c=2;$c<=$f_count;$c++){
 
  db_query("INSERT INTO bj_wordflash_test_missed_word VALUES('$id','','".$arr[2][$c]['level']."','".$arr[2][$c]['attempt']."','".$arr[2][$c]['question']."','".$arr[2][$c]['answer']."')");

   }
 }
 


  
}


