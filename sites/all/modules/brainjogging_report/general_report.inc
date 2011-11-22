<?php


function general_report($args){
  
  switch($args){
    case 'list':
      return bj_general_report_list();
      break;
    case 'create':
      return  drupal_get_form('bj_general_report_form');
      break;
    
    
  }
}

function bj_general_report_form(){
  bj_add_date_js();


  $form['from_date'] = array(
    '#type' => 'textfield',
    '#title' => t('From Date'),
    '#size' => 25,
    '#maxlength' => 30,
    '#weight' => 1,
  );
  $form['to_date'] = array(
    '#type' => 'textfield',
    '#title' => t('To date'),
    '#size' => 25,
     '#maxlength' => 30,
    '#weight' => 2,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Save'),
    '#value'=> t('Submit'),
    '#weight' => 3,
  );
    $form['user'] = array(
   '#type' => 'select',
   '#weight' => 0,
   '#title' => t('Select user'), 
   '#default_value' => $node->body,
   '#options' => bj_general_report_get_user(),
   

    );
  return $form;
}
function bj_general_report_get_user(){
  global $user;
 
    if(in_array('site administrator',$user->roles))
    {
      $fetch_user=db_query("SELECT t1.value,t2.uid FROM  profile_values t1 , users t2 ,  users_roles t4 where   (t4.rid=7 or t4.rid=6)  and t1.fid=1   and t2.uid=t1.uid   and t4.uid=t2.uid group by t1.value");
      while($res=db_fetch_object($fetch_user)){
	$user_list[$res->uid] = $res->value;
      }
      return $user_list;
    }
    
   if(in_array('teacher',$user->roles))
    {
      $fetch_user=db_query("SELECT t1.value ,t2.uid FROM  profile_values t1 , users t2 , bj_user_teachers t3 ,users_roles t4 where   (t4.rid=7 or t4.rid=6)  and t1.fid=1   and   t3.tid ='".$user->uid."' and t2.uid=t1.uid   and t4.uid=t2.uid and t3.uid=t2.uid group by t1.value");
      while($res=db_fetch_object($fetch_user)){
	$user_list[$res->uid] = $res->value;
      }
      return $user_list;
    }
  
  
}
function bj_general_report_list(){
        
    $bj=$_SESSION['bj_general'];
   
  
  
  $header = array(
    array('data' => t('First Name')),
    array('data' => t('Last Name')),
    array('data' => t('Start Date')),
    array('data' => t('User Id')),
    array('data' => t('School Name')),
    array('data' => t('Teacher Name')),
    array('data' => t('Report Date'))
		
  );
  
  $header1 = array(
    array('data' => t(' Total Activity')),
	  array('data' => t(' Average Speed')),
 
  );
   $header2 = array(
    array('data' => t('Total Activity')),
    array('data' => t('high level')),
    array('data' => t('high grade')),
    array('data' => t('Average level')),
    array('data' => t('Average grade')),
    array('data' => t('Per Day Activity')),
    array('data' => t('Per Five Day')),
    array('data' => t('Per Seven Day')),
  );
   $header3 = array(
    array('data' => t('Total Activity')),
    array('data' => t('high level')),
    array('data' => t('high grade')),
    array('data' => t('Average level')),
    array('data' => t('Average grade')),
    array('data' => t('Per Day Activity')),
    array('data' => t('Per Five Day')),
    array('data' => t('Per Seven Day')),
  );
  
	
  $rows[] = array($bj['general']['first_name'],$bj['general']['last_name'],$bj['general']['start_date'],$bj['general']['user_id'],$bj['general']['school_name'],$bj['general']['teacher_name'],$bj['general']['report_date']);
  $rows1[]=array($bj['em']['em_total_activity'],$bj['em']['em_avg_speed']);
  $rows2[] = array($bj['lf']['two']['lf_total_activity'],$bj['lf']['two']['high_level'],$bj['lf']['two']['high_grade'],$bj['lf']['two']['avg_level'],$bj['lf']['two']['avg_grade'],$bj['lf']['two']['per_day_activity'],$bj['lf']['two']['per_fiveday_activity'],
		   $bj['lf']['two']['per_sevenday_activity']);
  $rows3[] = array($bj['lf']['three']['lf_total_activity'],$bj['lf']['three']['high_level'],$bj['lf']['three']['high_grade'],$bj['lf']['three']['avg_level'],$bj['lf']['three']['avg_grade'],$bj['lf']['three']['per_day_activity'],$bj['lf']['three']['per_fiveday_activity'],
		   $bj['lf']['three']['per_sevenday_activity']);
  $rows4[] = array($bj['lf']['four']['lf_total_activity'],$bj['lf']['four']['high_level'],$bj['lf']['four']['high_grade'],$bj['lf']['four']['avg_level'],$bj['lf']['four']['avg_grade'],$bj['lf']['four']['per_day_activity'],$bj['lf']['four']['per_fiveday_activity'],
		   $bj['lf']['four']['per_sevenday_activity']);
  $rows5[] = array($bj['wf']['two']['wf_total_activity'],$bj['wf']['two']['high_level'],$bj['wf']['two']['high_grade'],$bj['wf']['two']['avg_level'],$bj['wf']['two']['avg_grade'],$bj['wf']['two']['per_day_activity'],$bj['wf']['two']['per_fiveday_activity'],
		   $bj['wf']['two']['per_sevenday_activity']);
  $rows6[] = array($bj['wf']['three']['wf_total_activity'],$bj['wf']['three']['high_level'],$bj['wf']['three']['high_grade'],$bj['wf']['three']['avg_level'],$bj['wf']['three']['avg_grade'],$bj['wf']['three']['per_day_activity'],$bj['wf']['three']['per_fiveday_activity'],
		   $bj['wf']['three']['per_sevenday_activity']);
  $rows7[] = array($bj['wf']['four']['wf_total_activity'],$bj['wf']['four']['high_level'],$bj['wf']['four']['high_grade'],$bj['wf']['four']['avg_level'],$bj['wf']['four']['avg_grade'],$bj['wf']['four']['per_day_activity'],$bj['wf']['four']['per_fiveday_activity'],
		   $bj['wf']['four']['per_sevenday_activity']);

  if(!$rows) {
      $rows[] = array(
	array(
				
	    'data'    => t('There are currently no records.'),
	    'colspan' => 3, 
	    'align'   => 'center'
	  )
		 );
  }
  
   
  $output .=theme_box('General Information','');
  $output .= theme('table', $header, $rows,array('id' => 'gen_reoport'));
  $output .=theme_box('Eye Movement Info','');
  $output .= theme('table', $header1, $rows1,array('id' => 'gen_reoport'));
  $output .=theme_box('Letter Flash Info','');
  $output .=theme_box('','Two Letter');
  $output .= theme('table', $header2, $rows2,array('id' => 'gen_reoport'));
  $output .=theme_box('','Three Letter');
  $output .= theme('table', $header2, $rows3,array('id' => 'gen_reoport'));
  $output .=theme_box('','Four Letter');
  $output .= theme('table', $header2, $rows4,array('id' => 'gen_reoport'));
  $output .=theme_box('Word Flash Info','');
  $output .=theme_box('','Two words');
  $output .= theme('table', $header3, $rows5,array('id' => 'gen_reoport'));
  $output .=theme_box('','Three words');
  $output .= theme('table', $header3, $rows6,array('id' => 'gen_reoport'));
  $output .=theme_box('','Four words');
  $output .= theme('table', $header3, $rows7,array('id' => 'gen_reoport'));
  $output .= theme('pager', NULL, $limit, 0);
 
	return $output;
}



function bj_general_report_form_validate(&$form,&$form_state){


}

function bj_general_report_form_submit(&$form,&$form_state){
   
    $from_d = date('Y-m-d',strtotime($form_state['values']['from_date']));
    $to_d   = date('Y-m-d',strtotime($form_state['values']['to_date']));
    $user=user_load($form_state['values']['user']);
    
   
    $bj_user_general=array();
   
    if(!brainjogging_is_student())
    {
        $bj_user_general['general']['first_name']     = $user->profile_first_name;
        $bj_user_general['general']['last_name']      = $user->profile_last_name;
        $bj_user_general['general']['start_date']     = date('d-m-Y H:i:s', $user->created);
        $bj_user_general['general']['user_id']        = $user->uid;
        //school name
        $bj_user_general['general']['school_name']    = db_result(db_query("SELECT t1.school_name FROM bj_school t1, bj_user_schools t2 WHERE t2.uid = '%d' and t1.sid = t2.sid", $form_state['values']['user']));
        //school name end
        //teacher name
        $tid= db_result(db_query("SELECT tid  FROM {bj_user_teachers} WHERE uid = '%d'", $user -> uid));
        $teacher=user_load($tid);
        $bj_user_general['general']['teacher_name']    = $teacher->profile_first_name;
        //teacher name end
        $bj_user_general['general']['report_date']     = date('d-m-Y');
        $bj_user_general['general']['date_from']       = $from_d;
        $bj_user_general['general']['date_to']         = $to_d;
        //eye movement Result
        $bj_user_general['em']['em_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_eyemovement_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND stud_id= %d ",$user -> uid));
        $bj_user_general['em']['em_avg_speed']       =round(db_result(db_query("SELECT AVG(speed) FROM {bj_eyemovement_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND stud_id= %d ",$user -> uid)));
        
        //eye movement Result end
        
        //letter flash
        //total days
      
         $from_date  = strtotime($from_d);
         $to_date    = strtotime($to_d);
         $datediff   = $to_date - $from_date;
         $total_days = floor($datediff/(60*60*24));
        //total days end
        //two letter flash
         
	 
	 
        $bj_user_general['lf']['two']['lf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['two']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '10:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['two']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '16:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['two']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '17:01:01 PM' and '20:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['two']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '21:01:01 PM' and '04:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '2' AND stud_id= %d ",$user -> uid));
         $bj_two_letter_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2' AND stud_id= %d ",$user -> uid));
         $bj_user_general['lf']['two']['high_level']        = round($bj_two_letter_high ['high_level']);
         $bj_user_general['lf']['two']['high_grade']        = round($bj_two_letter_high ['high_grade'])."%";
         $bj_two_letter_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2' AND stud_id= %d ",$user -> uid));
         $bj_user_general['lf']['two']['avg_level']        = round($bj_two_letter_avg ['avg_level']);
         $bj_user_general['lf']['two']['avg_grade']        = round($bj_two_letter_avg ['avg_grade'])."%";
         
         $bj_user_general['lf']['two']['per_day_activity']     = round($bj_user_general['lf']['two']['lf_total_activity']/$total_days,2);
         $bj_user_general['lf']['two']['per_fiveday_activity'] = round($bj_user_general['lf']['two']['per_day_activity']*5,2);
         $bj_user_general['lf']['two']['per_sevenday_activity']= round($bj_user_general['lf']['two']['per_day_activity']*7,2);
         //two letter flash end
         //three letter flash
        $bj_user_general['lf']['three']['lf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3' AND stud_id= %d ",$user -> uid));
	$bj_user_general['lf']['three']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '10:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['three']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '16:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['three']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '17:01:01 PM' and '20:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['three']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '21:01:01 PM' and '04:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '3' AND stud_id= %d ",$user -> uid));
         $bj_three_letter_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3' AND stud_id= %d ",$user -> uid));
         $bj_user_general['lf']['three']['high_level']        =round($bj_three_letter_high ['high_level']);
         $bj_user_general['lf']['three']['high_grade']        =round($bj_three_letter_high ['high_grade'])."%";
         $bj_three_letter_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3' AND stud_id= %d ",$user -> uid));
         $bj_user_general['lf']['three']['avg_level']        = round($bj_three_letter_avg ['avg_level']);
         $bj_user_general['lf']['three']['avg_grade']        = round($bj_three_letter_avg ['avg_grade'])."%";
         $bj_user_general['lf']['three']['per_day_activity']     = round($bj_user_general['lf']['three']['lf_total_activity']/$total_days,2);
         $bj_user_general['lf']['three']['per_fiveday_activity'] = round($bj_user_general['lf']['three']['per_day_activity']*5,2);
         $bj_user_general['lf']['three']['per_sevenday_activity']= round($bj_user_general['lf']['three']['per_day_activity']*7,2);
         //three letter flash end
          //three letter flash
        $bj_user_general['lf']['four']['lf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4' AND stud_id= %d ",$user -> uid));
	$bj_user_general['lf']['four']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '10:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '4' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['four']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '16:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '4' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['four']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '17:01:01 PM' and '20:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '4' AND stud_id= %d ",$user -> uid));
        $bj_user_general['lf']['four']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '21:01:01 PM' and '04:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'  AND test_type = '4' AND stud_id= %d ",$user -> uid));
         $bj_four_letter_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4' AND stud_id= %d ",$user -> uid));
         $bj_user_general['lf']['four']['high_level']        = round($bj_four_letter_high ['high_level']);
         $bj_user_general['lf']['four']['high_grade']        = round($bj_four_letter_high ['high_grade'])."%";
         $bj_four_letter_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'AND stud_id= %d ",$user -> uid));
         $bj_user_general['lf']['four']['avg_level']         = round($bj_four_letter_avg ['avg_level']);
         $bj_user_general['lf']['four']['avg_grade']         = round($bj_four_letter_avg ['avg_grade'])."%";
         $bj_user_general['lf']['four']['per_day_activity']     = round($bj_user_general['lf']['four']['lf_total_activity']/$total_days,2);
         $bj_user_general['lf']['four']['per_fiveday_activity'] = round($bj_user_general['lf']['four']['per_day_activity']*5,2);
         $bj_user_general['lf']['four']['per_sevenday_activity']= round($bj_user_general['lf']['four']['per_day_activity']*7,2);
         //three letter flash end
        //letter flash end
        
     //word flash
        
        //two word flash
        $bj_user_general['wf']['two']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '10:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['two']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '16:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['two']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '17:01:01 PM' and '20:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['two']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '21:01:01 PM' and '04:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '2' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['two']['wf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
         $bj_two_word_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2' AND stud_id= %d ",$user -> uid));
         $bj_user_general['wf']['two']['high_level']        = round($bj_two_word_high ['high_level']);
         $bj_user_general['wf']['two']['high_grade']        = round($bj_two_word_high ['high_grade'])."%";
         $bj_two_word_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2' AND stud_id= %d ",$user -> uid));
         $bj_user_general['wf']['two']['avg_level']        = round($bj_two_word_avg ['avg_level']);
         $bj_user_general['wf']['two']['avg_grade']        = round($bj_two_word_avg ['avg_grade'])."%";
         
         $bj_user_general['wf']['two']['per_day_activity']     = round($bj_user_general['wf']['two']['wf_total_activity']/$total_days,2);
         $bj_user_general['wf']['two']['per_fiveday_activity'] = round($bj_user_general['wf']['two']['per_day_activity']*5,2);
         $bj_user_general['wf']['two']['per_sevenday_activity']= round($bj_user_general['wf']['two']['per_day_activity']*7,2);
         //two word flash end
         //three word flash
        $bj_user_general['wf']['three']['wf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['three']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '10:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['three']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '16:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['three']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '17:01:01 PM' and '20:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '3' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['three']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '21:01:01 PM' and '04:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '3' AND stud_id= %d ",$user -> uid));
         $bj_three_word_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3' AND stud_id= %d ",$user -> uid));
         $bj_user_general['wf']['three']['high_level']        = round($bj_three_word_high ['high_level']);
         $bj_user_general['wf']['three']['high_grade']        = round($bj_three_word_high ['high_grade'])."%";
         $bj_three_word_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3' AND stud_id= %d ",$user -> uid));
         $bj_user_general['wf']['three']['avg_level']         = round($bj_three_word_avg ['avg_level']);
         $bj_user_general['wf']['three']['avg_grade']         = round($bj_three_word_avg ['avg_grade'])."%";
         $bj_user_general['wf']['three']['per_day_activity']     = round($bj_user_general['wf']['three']['wf_total_activity']/$total_days,2);
         $bj_user_general['wf']['three']['per_fiveday_activity'] = round($bj_user_general['wf']['three']['per_day_activity']*5,2);
         $bj_user_general['wf']['three']['per_sevenday_activity']= round($bj_user_general['wf']['three']['per_day_activity']*7,2);
         //three word flash end
          //three word flash
	 
        $bj_user_general['wf']['four']['wf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4' AND stud_id= %d ",$user -> uid));
	$bj_user_general['wf']['four']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '10:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '4' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['four']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '16:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '4' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['four']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '17:01:01 PM' and '20:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '4' AND stud_id= %d ",$user -> uid));
        $bj_user_general['wf']['four']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '21:01:01 PM' and '04:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type = '4' AND stud_id= %d ",$user -> uid));
         $bj_four_word_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4' AND stud_id= %d ",$user -> uid));
         $bj_user_general['wf']['four']['high_level']        = round($bj_four_word_high ['high_level']);
         $bj_user_general['wf']['four']['high_grade']        = round($bj_four_word_high ['high_grade'])."%";
         $bj_four_word_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4' AND stud_id= %d ",$user -> uid));
         $bj_user_general['wf']['four']['avg_level']         = round($bj_four_word_avg ['avg_level']);
         $bj_user_general['wf']['four']['avg_grade']         = round($bj_four_word_avg ['avg_grade'])."%";
         $bj_user_general['wf']['four']['per_day_activity']     = round($bj_user_general['wf']['four']['lf_total_activity']/$total_days,2);
         $bj_user_general['wf']['four']['per_fiveday_activity'] = round($bj_user_general['wf']['four']['per_day_activity']*5,2);
         $bj_user_general['wf']['four']['per_sevenday_activity']= round($bj_user_general['wf']['four']['per_day_activity']*7,2);
         //three word flash end
        //word flash end
       
         $_SESSION['bj_general'] = $bj_user_general;
         $form_state['redirect'] = 'brainjogging/report/general_report';
 
    } 
}
function bj_add_date_js(){
  $path = drupal_get_path('module', 'brainjogging_report');
  drupal_add_css($path.'/css/cal.css', 'module', 'all', FALSE);
  drupal_add_js($path.'/js/cal.js');
  drupal_add_js("jQuery(document).ready(function () { $('input.form-text').simpleDatepicker({ startdate: 2000, enddate: 2012 }); });",'inline');

}
