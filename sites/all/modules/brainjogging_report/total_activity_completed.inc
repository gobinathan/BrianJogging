<?php
function total_activity_completed_report($args){
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
       
        $total_activity_completed=array();
        $res =db_query("SELECT t2.title, t1.speed, DATE_FORMAT(t1.date,'%e-%m-%Y, %h:%m:%s') as date FROM `bj_eyemovement_test` t1, node t2 WHERE t1.wl_id = t2.vid AND t1.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."'");
        
        
       while($total_activity_completed['eye_movement'][]=db_fetch_array($res)){
            
        }
       
      $res1=db_query("SELECT highest_level, DATE_FORMAT(date, '%e-%m-%Y, %h:%m:%s' ) AS date, percentage,test_type FROM `bj_letterflash_test` WHERE date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."'");
       
       
       while($total_activity_completed['letter_flash'][]=db_fetch_array($res1)){
            
        }
        
        $res1=db_query("SELECT highest_level, DATE_FORMAT(date, '%e-%m-%Y, %h:%m:%s' ) AS date, percentage ,test_type FROM `bj_wordflash_test` WHERE date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".date('Y-m-d',strtotime("+1 day"))."'");
       
       
       while($total_activity_completed['word_flash'][]=db_fetch_array($res1)){
            
        }
   print_r($total_activity_completed);
}

}