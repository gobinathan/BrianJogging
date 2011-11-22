<?php

function word_flash_submit($args){
  global $user;
   $tid= db_result(db_query("SELECT tid  FROM {bj_user_teachers} WHERE uid = '%d'", $user -> uid));
  $teacher=user_load($tid);
  $teacher_id  = $teacher->uid;
 $date = date('Y-m-d H:i:s');
 $rese   = $_POST["res"];
 
 //$var='{"status":{"wrong":4,"correct":2},"levels":[null,{"question":"Bilberry Blackberry","answer":"kjdkdf","result":0,"level":3,"attempt":1},{"question":"Bilberry Blackberry","answer":"kfkdfjksa","result":0,"level":3,"attempt":2},{"question":"Bilberry Blackberry","answer":"kjdfjkldjkl","result":0,"level":3,"attempt":3},{"question":"Bilberry Blackberry","answer":"djkjkfjka","result":0,"level":3,"attempt":4}],"res":{"res":{"attempts":4,"level":3,"ftype":"2","ftype_text":" Two Words Flash ","wordlist":"1","fsize":"medium"}},"pers":{"perecent":50},"tot_atem":{"tot":6}}';
 
 
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
 $my_res=db_query("INSERT INTO bj_wordflash_test VALUES('','".$user->uid."','$teacher_id','$date',".$arr[5][1][0].",".$arr[1][2][0].",".$arr[4][1][0].",".$arr[3][1]['level'].",".$arr[3][1]['ftype'].")");
 if($my_res){ 
  $id=mysql_insert_id();
  $f_count=count($arr[2]);
  for($c=2;$c<=$f_count;$c++){
 
  db_query("INSERT INTO bj_wordflash_test_missed_words VALUES('$id','','".$arr[2][$c]['level']."','".$arr[2][$c]['attempt']."','".$arr[2][$c]['question']."','".$arr[2][$c]['answer']."')");

   }
 }
 


  
}


