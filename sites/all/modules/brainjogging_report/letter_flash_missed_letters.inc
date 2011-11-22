<?php
function letter_flash_missed_letter_report($args){
  
  switch($args){
    case 'list':
      return bj_lf_report_list();
      break;
    case 'create':
      return  drupal_get_form('bj_lfmissed_report_form');
      break;
    
  }
}

function bj_lfmissed_report_form(){
  
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
   '#options' => bj_lf_report_get_user(),
   

    );
    
  return $form;
}
function bj_lf_report_get_user(){
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
function bj_lf_report_list(){

    $bj        = $_SESSION['bj_general'];
    $lf_missed = $_SESSION['lf_missed'];
 

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
    array('data' => t('Missed Letters')),
	  array('data' => t('Percentage')),
          
		
  );
   $header2 = array(
    array('data' => t('Correct Response')),
	  array('data' => t('Client Response')),
   
  );
   $header3 = array(
    array('data' => t('Possition Left')),
	  array('data' => t('Possition Right')),
   
  );
     $header4 = array(
    array('data' => t('Possition Left')),
    array('data' => t('Possition Center')),
	  array('data' => t('Possition Right')),
   
  );
        $header5 = array(
    array('data' => t('Possition Left')),
    array('data' => t('Possition Left Center')),
    array('data' => t('Possition Right Center')),
    array('data' => t('Possition Right')),
   
  );
  
	
	    $rows[] = array($bj['general']['first_name'],$bj['general']['last_name'],$bj['general']['start_date'],$bj['general']['user_id'],$bj['general']['school_name'],$bj['general']['teacher_name'],$bj['general']['report_date']);
            if(is_array($lf_missed['letter_percentage'])){   
                foreach($lf_missed['letter_percentage']  as $lf)
                {
                    $rows1[]=array($lf['ans'],round($lf['percent']).'%');
                  
                }
            }
           if(is_array($lf_missed['common_mistakes'])){
                foreach($lf_missed['common_mistakes']  as $cm)
                {
                    $rows2[]=array($cm['ques'],$cm['ans']);
                  
                } 
            }
                $rows3[]=array(round($lf_missed['pos']['type2'][1]['percent'])."%",round($lf_missed['pos']['type2'][0]['percent'])."%");
                $rows4[]=array(round($lf_missed['pos']['type3'][2]['percent'])."%",round($lf_missed['pos']['type3'][1]['percent'])."%",round($lf_missed['pos']['type3'][0]['percent'])."%");
                $rows5[]=array(round($lf_missed['pos']['type4'][3]['percent'])."%",round($lf_missed['pos']['type4'][2]['percent'])."%",round($lf_missed['pos']['type4'][1]['percent'])."%",round($lf_missed['pos']['type4'][0]['percent'])."%");
 
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
    $output .=theme_box('Missing Letter Percentage','');
    $output .= theme('table', $header1, $rows1,array('id' => 'lf_miss'));
    $output .=theme_box('Client Response and Correct Response','');
    $output .= theme('table', $header2, $rows2,array('id' => 'lf_miss'));
    $output .=theme_box('Wrong EntryPosition Percentage','');
    $output .=theme_box('','Two Letter Flash');
    $output .= theme('table', $header3, $rows3,array('id' => 'lf_miss'));
    $output .=theme_box('','Three Letter Flash');
    $output .= theme('table', $header4, $rows4,array('id' => 'lf_miss'));
    $output .=theme_box('','Four Letter Flash');
    $output .= theme('table', $header5, $rows5,array('id' => 'lf_miss'));
    $output .= theme('pager', NULL, $limit, 0);
 
	return $output;
}




function bj_lfmissed_report_form_submit(&$form,&$form_state){
    $from_d = date('Y-m-d',strtotime($form_state['values']['from_date']));
    $to_d   = date('Y-m-d',strtotime($form_state['values']['to_date']));
    
    $user=user_load($form_state['values']['user']);
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
       
        $letter_flash_missed=array();
       
        $res =db_query("SELECT t1.ans, count( t1.ans ) AS ansCount, count( t1.ans ) / (SELECT count( ans ) FROM bj_letterflash_test_missed_letters ) *100 AS percent
                 FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2 where t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' and t1.t_id=t2.t_id  AND t2.stud_id='".$user -> uid."' GROUP BY ans ORDER BY percent DESC  LIMIT 10");
        
       while($letter_flash_missed['letter_percentage'][]=db_fetch_array($res)){
            
        }
       
     
       
       
      $res1=db_query("SELECT t1.ques, t1.ans, COUNT(*) as count FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  where t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' and t1.t_id=t2.t_id  AND t2.stud_id='".$user -> uid."'GROUP BY t1.ques, t1.ans ORDER BY count limit 10");
      while($letter_flash_missed['common_mistakes'][]=db_fetch_array($res1)){
            
        }
        
        $res2=db_query("SELECT t1.pos, count( t1.pos ) AS ansCount, count( t1.pos ) / (SELECT count( t1.pos ) FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2 WHERE t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND t2.test_type = '2' AND t1.t_id = t2.t_id ) *100 AS percent
        FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  WHERE t2.test_type = '2'  AND t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' and t1.t_id=t2.t_id  AND t2.stud_id='".$user -> uid."' GROUP BY t1.pos  ORDER BY t1.pos DESC   ");
        while($letter_flash_missed['pos']['type2'][]=db_fetch_array($res2)){
            
        }
        $res3=db_query("SELECT t1.pos, count( t1.pos ) AS ansCount, count( t1.pos ) / (SELECT count( t1.pos ) FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2 WHERE t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND t2.test_type = '3' AND t1.t_id = t2.t_id ) *100 AS percent
        FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  WHERE t2.test_type = '3'  AND t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' and t1.t_id=t2.t_id  AND t2.stud_id='".$user -> uid."' GROUP BY t1.pos  ORDER BY t1.pos DESC  ");
        while($letter_flash_missed['pos']['type3'][]=db_fetch_array($res3)){
            
        }
        $res4=db_query("SELECT t1.pos, count( t1.pos ) AS ansCount, count( t1.pos ) / (SELECT count( t1.pos ) FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2 WHERE t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' AND t2.test_type = '4' AND t1.t_id = t2.t_id ) *100 AS percent
        FROM bj_letterflash_test_missed_letters t1, bj_letterflash_test t2  WHERE t2.test_type = '4'  AND t2.date BETWEEN '".$bj_user_general['general']['date_from']."' AND '".$bj_user_general['general']['date_to']."' and t1.t_id=t2.t_id  AND t2.stud_id='".$user -> uid."' GROUP BY t1.pos  ORDER BY t1.pos DESC   ");
        while($letter_flash_missed['pos']['type4'][]=db_fetch_array($res4)){
         
        }
         $_SESSION['bj_general'] = $bj_user_general;
         $_SESSION['lf_missed'] = $letter_flash_missed;
         $form_state['redirect'] = 'brainjogging/report/letter_flash_missed_letters_report';  
}

}
function bj_add_date_js(){
  $path = drupal_get_path('module', 'brainjogging_report');
  drupal_add_css($path.'/css/cal.css', 'module', 'all', FALSE);
  drupal_add_js($path.'/js/cal.js');
  drupal_add_js("jQuery(document).ready(function () { $('input.form-text').simpleDatepicker({ startdate: 2000, enddate: 2012 }); });",'inline');

}