<?php
function word_flash_missed_word_report($args){
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
       
        $word_flash_missed=array();
        $res =db_query("SELECT t1.ques,t1.ans FROM bj_wordflash_test_missed_words t1, bj_wordflash_test t2 where t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."' and t1.t_id=t2.t_id    LIMIT 5");
        
        
       while($word_flash_missed['missed_words'][]=db_fetch_array($res)){
            
        }
       
     
       
     
   print_r($word_flash_missed);
}

}