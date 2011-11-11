<?php
function letter_flash_missed_letter_report($args){
    global $user;
    $bj_user_general=array();
    echo "<pre>";
    if(brainjogging_is_student())
    {
        $m=6;
        $month="-".$m." months";
               
        $bj_user_general['general']['fist_name']    = $user->profile_first_name;
        $bj_user_general['general']['last_name']    = $user->profile_last_name;
        $bj_user_general['general']['start_date']   = date('d-m-Y H:i:s', $user->created);
        $bj_user_general['general']['user_id']      = $user->uid;
        //school name
        $bj_user_general['general']['school_name']   = db_result(db_query("SELECT t1.school_name FROM bj_school t1, bj_user_schools t2 WHERE t2.uid = '%d' and t1.sid = t2.sid", $user -> uid));
        //school name end
        //teacher name
        $tid= db_result(db_query("SELECT tid  FROM {bj_user_teachers} WHERE uid = '%d'", $user -> uid));
        $teacher=user_load($tid);
        $bj_user_general['general']['teacher_name']  = $teacher->profile_first_name;
        //teacher name end
        $bj_user_general['general']['report_date']    = date('d-m-Y');
        $bj_user_general['general']['date_from']       =date("Y-m-d", strtotime($month));
       
        $letter_flash_missed=array();
        $res =db_query("SELECT t1.ans, count( t1.ans ) AS ansCount, count( t1.ans ) / (SELECT count( ans ) FROM bj_letterflash_test_missed_letters ) *100 AS percent
                 FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2 where t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."' and t1.t_id=t2.t_id  GROUP BY ans ORDER BY percent DESC  LIMIT 5");
        
       while($letter_flash_missed['letter_percentage'][]=db_fetch_array($res)){
            
        }
       
     
       
       
      $res1=db_query("SELECT t1.ques, t1.ans, COUNT(*) as count FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  where t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."' and t1.t_id=t2.t_id GROUP BY t1.ques, t1.ans ORDER BY count limit 10");
      while($letter_flash_missed['common_mistakes'][]=db_fetch_array($res1)){
            
        }
        
        
       $res2=db_query("SELECT t1.pos, count( t1.pos ) AS ansCount, count( t1.pos ) / (SELECT count( pos ) FROM bj_letterflash_test_missed_letters ) *100 AS percent
        FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  WHERE t2.test_type = '2'  AND t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."' and t1.t_id=t2.t_id  GROUP BY t1.pos  ORDER BY percent DESC  LIMIT 5 ");
        while($letter_flash_missed['pos']['type2'][]=db_fetch_array($res2)){
            
        }
        $res3=db_query("SELECT t1.pos, count( t1.pos ) AS ansCount, count( t1.pos ) / (SELECT count( pos ) FROM bj_letterflash_test_missed_letters ) *100 AS percent
        FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  WHERE t2.test_type = '3'  AND t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."' and t1.t_id=t2.t_id  GROUP BY t1.pos  ORDER BY percent DESC  LIMIT 5 ");
        while($letter_flash_missed['pos']['type3'][]=db_fetch_array($res3)){
            
        }
        $res4=db_query("SELECT t1.pos, count( t1.pos ) AS ansCount, count( t1.pos ) / (SELECT count( pos ) FROM bj_letterflash_test_missed_letters ) *100 AS percent
        FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  WHERE t2.test_type = '4'  AND t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."' and t1.t_id=t2.t_id  GROUP BY t1.pos  ORDER BY percent DESC  LIMIT 5 ");
        while($letter_flash_missed['pos']['type4'][]=db_fetch_array($res4)){
            
        }
   print_r($letter_flash_missed);
}

}