<?php


function general_report($args){
  
  switch($args){
    case 'list':
      return bj_general_report_list();
      break;
    case 'create':
      return  drupal_get_form('bj_general_report_form');
      break;
    case 'edit':
      return drupal_get_form('bj_grade_create_form');
      break;
    case 'delete':
      return drupal_get_form('bj_greade_delete_confirm');
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
    '#weight' => 0,
  );
  $form['to_date'] = array(
    '#type' => 'textfield',
    '#title' => t('To date'),
    '#size' => 25,
     '#maxlength' => 30,
    '#weight' => 1,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#title' => t('Save'),
    '#value'=> t('Submit'),
    '#weight' => 2,
  );
    
  return $form;
}

function bj_general_report_list(){
        
    $bj=$_SESSION['bj_general'];
     //echo "<pre>";
     //print_r($bj['general']['first_name']);
     //print_r($bj);
     //
     //exit();
  $limit = 5;
  
  
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
    array('data' => t('Eye Movement Total Activity')),
	  array('data' => t('Eye Movement Average Speed')),
          
		
  );
   $header2 = array(
    array('data' => t('Letter Flash Total Activity')),
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
 
	if(!$rows) {
	    $rows[] = array(
                        array(
                                                
                            'data'    => t('There are currently no records.'),
                            'colspan' => 3, 
                            'align'   => 'center'
                          )
                       );
        }
  
	$output .= theme('table', $header, $rows);
        $output .= theme('table', $header1, $rows1);
        $output .= theme('table', $header2, $rows2);
         $output .= theme('table', $header2, $rows3);
         $output .= theme('table', $header2, $rows4);
        $output .= theme('pager', NULL, $limit, 0);
 
	return $output;
}



function bj_general_report_form_validate(&$form,&$form_state){
  ////date convert array to string
  //$month = $form_state['values']['from_date']['month'];
  //$day = $form_state['values']['from_date']['day'];
  //$year = $form_state['values']['from_date']['year'];
  //$month1 = $form_state['values']['to_date']['month'];
  //$day1 = $form_state['values']['to_date']['day'];
  //$year1 = $form_state['values']['to_date']['year'];
  //$f_date = $day."-"."$month"."-".$year;
  //$t_date = $day1."-"."$month1"."-".$year1;
  //$form_state['values']['from_date']= $f_date;
  //$form_state['values']['to_date']= $t_date;
  ////date convert array to string end

}

function bj_general_report_form_submit(&$form,&$form_state){
    
   
    
    $from_d = date('Y-m-d',strtotime($form_state['values']['from_date']));
    $to_d   = date('Y-m-d',strtotime($form_state['values']['to_date']));
    
   
    global $user;
    $bj_user_general=array();
   
    if(brainjogging_is_student())
    {
        $bj_user_general['general']['first_name']     = $user->profile_first_name;
        $bj_user_general['general']['last_name']      = $user->profile_last_name;
        $bj_user_general['general']['start_date']     = date('d-m-Y H:i:s', $user->created);
        $bj_user_general['general']['user_id']        = $user->uid;
        //school name
        $bj_user_general['general']['school_name']    = db_result(db_query("SELECT t1.school_name FROM bj_school t1, bj_user_schools t2 WHERE t2.uid = '%d' and t1.sid = t2.sid", $user -> uid));
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
        $bj_user_general['em']['em_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_eyemovement_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['em']['em_avg_speed']     = db_result(db_query("SELECT AVG(speed) FROM {bj_eyemovement_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        
        //eye movement Result end
        
        //letter flash
        //total days
        // $now = time(); // or your date as well
       // $your_date = strtotime(date("Y-m-d", strtotime("-6 months")));
         $from_date  = strtotime($from_d);
         $to_date    = strtotime($to_d);
         $datediff   = $to_date - $from_date;
         $total_days = floor($datediff/(60*60*24));
        //tatal days end
        //two letter flash
        
        $bj_user_general['lf']['two']['lf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
        $bj_user_general['lf']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '11:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['lf']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '05:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['lf']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 PM' and '09:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['lf']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_letterflash_test` WHERE DATE_FORMAT(date,'%r') between '09:01:01 PM' and '05:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
         $bj_two_letter_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
         $bj_user_general['lf']['two']['high_level']        = $bj_two_letter_high ['high_level'];
         $bj_user_general['lf']['two']['high_grade']        = $bj_two_letter_high ['high_grade'];
         $bj_two_letter_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
         $bj_user_general['lf']['two']['avg_level']        = $bj_two_letter_avg ['avg_level'];
         $bj_user_general['lf']['two']['avg_grade']        = $bj_two_letter_avg ['avg_grade'];
         
         $bj_user_general['lf']['two']['per_day_activity']     = round($bj_user_general['lf']['two']['lf_total_activity']/$total_days,2);
         $bj_user_general['lf']['two']['per_fiveday_activity'] = round($bj_user_general['lf']['two']['per_day_activity']*5,2);
         $bj_user_general['lf']['two']['per_sevenday_activity']= round($bj_user_general['lf']['two']['per_day_activity']*7,2);
         //two letter flash end
         //three letter flash
        $bj_user_general['lf']['three']['lf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3'"));
         $bj_three_letter_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3'"));
         $bj_user_general['lf']['three']['high_level']        = $bj_three_letter_high ['high_level'];
         $bj_user_general['lf']['three']['high_grade']        = $bj_three_letter_high ['high_grade'];
         $bj_three_letter_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3'"));
         $bj_user_general['lf']['three']['avg_level']        = $bj_three_letter_avg ['avg_level'];
         $bj_user_general['lf']['three']['avg_grade']        = $bj_three_letter_avg ['avg_grade'];
         $bj_user_general['lf']['three']['per_day_activity']     = round($bj_user_general['lf']['three']['lf_total_activity']/$total_days,2);
         $bj_user_general['lf']['three']['per_fiveday_activity'] = round($bj_user_general['lf']['three']['per_day_activity']*5,2);
         $bj_user_general['lf']['three']['per_sevenday_activity']= round($bj_user_general['lf']['three']['per_day_activity']*7,2);
         //three letter flash end
          //three letter flash
        $bj_user_general['lf']['four']['lf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'"));
         $bj_four_letter_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'"));
         $bj_user_general['lf']['four']['high_level']        = $bj_four_letter_high ['high_level'];
         $bj_user_general['lf']['four']['high_grade']        = $bj_four_letter_high ['high_grade'];
         $bj_four_letter_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_letterflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'"));
         $bj_user_general['lf']['four']['avg_level']         = $bj_four_letter_avg ['avg_level'];
         $bj_user_general['lf']['four']['avg_grade']         = $bj_four_letter_avg ['avg_grade'];
         $bj_user_general['lf']['four']['per_day_activity']     = round($bj_user_general['lf']['four']['lf_total_activity']/$total_days,2);
         $bj_user_general['lf']['four']['per_fiveday_activity'] = round($bj_user_general['lf']['four']['per_day_activity']*5,2);
         $bj_user_general['lf']['four']['per_sevenday_activity']= round($bj_user_general['lf']['four']['per_day_activity']*7,2);
         //three letter flash end
        //letter flash end
        
    }   //word flash
        
        //two word flash
        $bj_user_general['wf']['time']['fiveam_elevenam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 AM' and '11:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['wf']['time']['elevenam_fivepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '11:01:01 AM' and '05:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['wf']['time']['fivepm_ninepm_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '05:01:01 PM' and '09:59:59 PM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['wf']['time']['ninepm_fiveam_activity']=db_result(db_query("SELECT COUNT(*) from `bj_wordflash_test` WHERE DATE_FORMAT(date,'%r') between '09:01:01 PM' and '05:59:59 AM' and date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."'"));
        $bj_user_general['wf']['two']['wf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
         $bj_two_word_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
         $bj_user_general['wf']['two']['high_level']        = $bj_two_word_high ['high_level'];
         $bj_user_general['wf']['two']['high_grade']        = $bj_two_word_high ['high_grade'];
         $bj_two_word_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='2'"));
         $bj_user_general['wf']['two']['avg_level']        = $bj_two_word_avg ['avg_level'];
         $bj_user_general['wf']['two']['avg_grade']        = $bj_two_word_avg ['avg_grade'];
         
         $bj_user_general['wf']['two']['per_day_activity']     = round($bj_user_general['wf']['two']['wf_total_activity']/$total_days,2);
         $bj_user_general['wf']['two']['per_fiveday_activity'] = round($bj_user_general['wf']['two']['per_day_activity']*5,2);
         $bj_user_general['wf']['two']['per_sevenday_activity']= round($bj_user_general['wf']['two']['per_day_activity']*7,2);
         //two word flash end
         //three word flash
        $bj_user_general['wf']['three']['wf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3'"));
         $bj_three_word_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3'"));
         $bj_user_general['wf']['three']['high_level']        = $bj_three_word_high ['high_level'];
         $bj_user_general['wf']['three']['high_grade']        = $bj_three_word_high ['high_grade'];
         $bj_three_word_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='3'"));
         $bj_user_general['wf']['three']['avg_level']        = $bj_three_word_avg ['avg_level'];
         $bj_user_general['wf']['three']['avg_grade']        = $bj_three_word_avg ['avg_grade'];
         $bj_user_general['wf']['three']['per_day_activity']     = round($bj_user_general['wf']['three']['wf_total_activity']/$total_days,2);
         $bj_user_general['wf']['three']['per_fiveday_activity'] = round($bj_user_general['wf']['three']['per_day_activity']*5,2);
         $bj_user_general['wf']['three']['per_sevenday_activity']= round($bj_user_general['wf']['three']['per_day_activity']*7,2);
         //three word flash end
          //three word flash
        $bj_user_general['wf']['four']['wf_total_activity']  = db_result(db_query("SELECT COUNT(*) FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'"));
         $bj_four_word_high        = db_fetch_array(db_query("SELECT MAX(highest_level) high_level,MAX(percentage) high_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'"));
         $bj_user_general['wf']['four']['high_level']        = $bj_four_word_high ['high_level'];
         $bj_user_general['wf']['four']['high_grade']        = $bj_four_word_high ['high_grade'];
         $bj_four_word_avg        = db_fetch_array(db_query("SELECT AVG(highest_level) avg_level,AVG(percentage) avg_grade FROM {bj_wordflash_test} where date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND test_type='4'"));
         $bj_user_general['wf']['four']['avg_level']         = $bj_four_word_avg ['avg_level'];
         $bj_user_general['wf']['four']['avg_grade']         = $bj_four_word_avg ['avg_grade'];
         $bj_user_general['wf']['four']['per_day_activity']     = round($bj_user_general['wf']['four']['lf_total_activity']/$total_days,2);
         $bj_user_general['wf']['four']['per_fiveday_activity'] = round($bj_user_general['wf']['four']['per_day_activity']*5,2);
         $bj_user_general['wf']['four']['per_sevenday_activity']= round($bj_user_general['wf']['four']['per_day_activity']*7,2);
         //three word flash end
        //word flash end
        //echo "<pre>";
        //print_r($bj_user_general);
        //exit;
        //
        
        
        
         $_SESSION['bj_general'] = $bj_user_general;
         $form_state['redirect'] = 'brainjogging/general_report';
  //drupal_goto('brainjogging/general_report');
//return  $bj_user_general;
   
}
function bj_add_date_js(){
  $path = drupal_get_path('module', 'brainjogging_report');
  drupal_add_css($path.'/css/cal.css', 'module', 'all', FALSE);
  drupal_add_js($path.'/js/cal.js');
  drupal_add_js("jQuery(document).ready(function () { $('input.form-text').simpleDatepicker({ startdate: 2000, enddate: 2012 }); });",'inline');

}
