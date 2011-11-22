<?php
function total_activity_completed_report($args){
  
  switch($args){
    case 'list':
      return bj_total_activity_report_list();
      break;
    case 'create':
      return  drupal_get_form('bj_total_activity_report_form');
      break;
    
  }
}

function bj_total_activity_report_form(){
  
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
   '#options' => bj_total_activity_report_get_user(),
   

    );
    
  return $form;
}
function bj_total_activity_report_get_user(){
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
function bj_total_activity_report_list(){
        
    $bj             = $_SESSION['bj_general'];
    $total_activity = $_SESSION['total_activity'];
  
  
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
  
	  array('data' => t('Speed')),
           array('data' => t('WordList Name')),
            array('data' => t('Date & Time')),
          
		
  );
  $header2 = array(
  
	  array('data' => t('High Level')),
           array('data' => t('Grade')),
            array('data' => t('Date & Time')),
          
		
  );
   $header3 = array(
  
	  array('data' => t('High Level')),
           array('data' => t('Grade')),
            array('data' => t('Date & Time')),
          
		
  );
   
	
	    $rows[] = array($bj['general']['first_name'],$bj['general']['last_name'],$bj['general']['start_date'],$bj['general']['user_id'],$bj['general']['school_name'],$bj['general']['teacher_name'],$bj['general']['report_date']);
             if(is_array($total_activity['eye_movement'])) {  
                foreach($total_activity['eye_movement']  as $key => $eye)
                {
                    $rows1[]=array($eye['title'],$eye['speed'],$eye['date']);
                  
                }
            }
            if(is_array($total_activity['letter_flash'])){
                foreach($total_activity['letter_flash']  as $key => $lf)
                {
                   $rows2[]=array($lf['highest_level'],$lf['percentage'],$lf['date']);
                }
            }
            if(is_array($total_activity['word_flash'])){
                foreach($total_activity['word_flash']  as $key => $wf)
               {
                   $rows3[]=array($wf['highest_level'],$wf['percentage'],$wf['date']);
                 
               }
            }
           
            
 
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
	$output .= theme('table', $header,  $rows, array('id' => 'lf_miss'));
        $output .=theme_box('Eye Movement Activities','');
        $output .= theme('table', $header1, $rows1,array('id' => 'lf_miss'));
        $output .=theme_box('Letter Flash Activities','');
        $output .= theme('table', $header2, $rows2,array('id' => 'lf_miss'));
        $output .=theme_box('Word Flash Activities','');
        $output .= theme('table', $header3, $rows3,array('id' => 'lf_miss'));
	
        $output .= theme('pager', NULL, $limit, 0);
 
	return $output;
}

function bj_total_activity_report_form_submit(&$form,&$form_state){
    $user=user_load($form_state['values']['user']);
    $from_d = date('Y-m-d',strtotime($form_state['values']['from_date']));
    $to_d   = date('Y-m-d',strtotime($form_state['values']['to_date']));
    $bj_user_general=array();
   
    if(!brainjogging_is_student())
    {
                       
        $bj_user_general['general']['first_name']    = $user->profile_first_name;
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
        $bj_user_general['general']['date_from']       = $from_d;
        $bj_user_general['general']['date_to']         = $to_d;
        $total_activity_completed=array();
        $res = db_query("SELECT t2.title, t1.speed, DATE_FORMAT(t1.date,'%e-%m-%Y, %h:%m:%s') as date FROM `bj_eyemovement_test` t1, node t2 WHERE t1.wl_id = t2.vid AND t1.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND stud_id ='".$user -> uid."'");
        
       
       while($total_activity_completed['eye_movement'][]=db_fetch_array($res)){
            
        }
   
       
      $res1=db_query("SELECT highest_level, DATE_FORMAT(date, '%e-%m-%Y, %h:%m:%s' ) AS date, percentage,test_type FROM `bj_letterflash_test` WHERE date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND stud_id ='".$user -> uid."'");
       
       
       while($total_activity_completed['letter_flash'][]=db_fetch_array($res1)){
            
        }
        
        $res1=db_query("SELECT highest_level, DATE_FORMAT(date, '%e-%m-%Y, %h:%m:%s' ) AS date, percentage ,test_type FROM `bj_wordflash_test` WHERE date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND stud_id ='".$user -> uid."'");
       
       
       while($total_activity_completed['word_flash'][]=db_fetch_array($res1)){
            
        }
   
    $_SESSION['bj_general'] = $bj_user_general;
    $_SESSION['total_activity'] = $total_activity_completed;
    $form_state['redirect'] = 'admin/brainjogging/report/total_activity_completed_report/%';  
}

}
function bj_add_date_js(){
  $path = drupal_get_path('module', 'brainjogging_report');
  drupal_add_css($path.'/css/cal.css', 'module', 'all', FALSE);
  drupal_add_js($path.'/js/cal.js');
  drupal_add_js("jQuery(document).ready(function () { $('input.form-text').simpleDatepicker({ startdate: 2000, enddate: 2012 }); });",'inline');

}