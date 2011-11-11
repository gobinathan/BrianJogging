<?php

function letter_flash_submit($args){
 $date = date('Y-m-d H:i:s');
$rese   = $_POST["res"];
//$rese='{"1":{"1":{"qn_chars":["l","m"],"ans_chars":["l","m"]}},"2":{"1":{"qn_chars":["h","i"],"ans_chars":["h","i"]}},"3":{"1":{"qn_chars":["f","e"],"ans_chars":["f","e"]}},"4":{"1":{"qn_chars":["q","s"],"ans_chars":["s",""]},"2":{"qn_chars":["f","t"],"ans_chars":["s","l"]},"3":{"qn_chars":["h","s"],"ans_chars":["k","d"]}},"type":[2],"result":{"lev":[4,4,4,4,4,4],"subl":[1,1,2,2,3,3],"qn":["q","s","f","t","h","s"],"ans":["s","","s","l","k","d"],"pos":[1,2,1,2,1,2]},"res":{"t_at":6,"c_at":3,"level":3,"grade":50}}';

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




 $my_res=db_query("INSERT INTO bj_letterflash_test VALUES('','','','$date','".$result->res->t_at."','".$result->res->c_at."','".$result->res->level."','".$result->res->grade."','".$result->type[0]."')");
 
 if($my_res){ 
  $id=mysql_insert_id();
  $f_count=count($result->result->lev);
  for($c=0;$c<$f_count;$c++){
 
  db_query("INSERT INTO bj_letterflash_test_missed_letters VALUES('$id','','".$result->result->lev[$c]."','".$result->result->subl[$c]."','".$result->result->pos[$c]."','".$result->result->qn[$c]."','".$result->result->ans[$c]."')");

   }
 }
 
 


  
}


