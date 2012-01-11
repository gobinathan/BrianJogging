<div id="container" >
   <?php if($_SESSION['brainjogging']['eye_test']!=true){ ?>
  
  <!-- Eye movement Start-->
 <?php

 ?>
    <div id="em_letter" style="position:absolute;">
      <span id="em_move"> </span>
    </div>
    <div id="em_init" style="border:1px dotted gray; width:400px;padding:10px;font-size:15px;text-align:justify; position:relative;height:300px; margin:0px auto; display:none;">
      <center><b> Brain jogging's Eye Movement<br/>
      Exercise</b></center><br/><br/>
      Welcome to  brain Jogging. You must complete <span id="eyecount">Three</span>
      Eye Movement activities before useing any other activities.
      You will now be directed to the Eye Movement activity.
      <br/><br/>
      <center>
         <div>
        <span>Font Size :</span>
        <input type="radio" name="wf_settings_fsize" value="small">Small
        <input type="radio" name="wf_settings_fsize" checked="checked" value="medium">Medium
        <input type="radio" name="wf_settings_fsize" value="large">large
        <div id="wf_settings_font">Font Size</div>
      </div>
      <?php if(!brainjogging_is_student() || $_SESSION['brainjogging']['eye_test']==true){ ?>
      <input type="button" value="Skip Eye Movement" id="em_main">
      <input type="button" value="Next" id="em_next">
      <?php  }
      else{ ?>
      <input type="button" value="Next" id="em_next">
      <?php }?>
      
      </center>
    </div>
    <?php if(!brainjogging_is_student() || $_SESSION['brainjogging']['eye_test']==true){ ?>
    
    <?php  }
      else{  }?>
    <div id="em_instuct" style="border:1px dotted gray; display:none; width:400px;padding:10px;font-size:15px;text-align:justify; position:relative;height:300px; margin:0px auto;">
      <center><b>Direction for Eye Movemnt</b></center><br>
      A word or phrase will be flahed  to the right and left sides of the screen. The words to be clled aloud are the first word on the far left and the last
      word on the far right. Students should say the word on the far left. Spell the word,
      and say the word again. Do the same with the word on the far right.<br>
      If is important that you say the word aloud and not silently in your mind student must
      also keep their head still and more theri eyes left to right.<br>
      Click "Next" button below to begin exercise.<br><br>
      <center> <input type="button" value="next" id="em_start"></center>
    </div>
 
  <?php }
  else{
  ?>
  <div id="em_letter" style="position:absolute;">
      <span id="em_move"> </span>
    </div>
   <div id="ses_menu" style="border:1px dotted gray;  width:400px; position:relative;height:300px; margin:0px auto;">
      <center><b>Brain jogging's Eye Movement</b></center>
      <br><br>
      Select Your Choice:
      <br><br>
      <center>
      <select name="option_eyemove" id="option_eyemove">
        <option >Eye Movement Activity</option>
        <option >Picture Flash</option>
        
      </select><br><br><br>
      <input type="button" value="Main Menu" id="em_main">
       <input type="button" value="next" id="ses_next"></center>
    </div>
 
  <div id="ses_wordlist" style="border:1px dotted gray;display:none;  width:400px; position:relative;height:300px; margin:0px auto;">
     
     <?php 
    
     ?><center><b>Brain jogging's Eye Movement</b></center>
      <br><br>
      Select a Wordlist for Eye movement:
      <br><br>
      <center>
       <span>Word Lists :</span>
       <select id="eye_wordlist">        
        <option value="0">-Select-</option>
        <?php
        foreach ($vars as $cat => $wlist){
          if(count($wlist['childs']) > 0){
            printf('<optgroup label="%s">', $wlist['title']);
            foreach ($wlist['childs'] as $wl){
             printf('<option value="%d">%s</option>',$wl->nid, $wl->title);
            }
            print "</optgroup>";
          }
        }
        ?>
       </select>
       
         <div style="margin-top:15px;">
        <span>Font Size :</span>
        <input type="radio" name="wf_settings_fsize" value="small">Small
        <input type="radio" name="wf_settings_fsize" checked="checked" value="medium">Medium
        <input type="radio" name="wf_settings_fsize" value="large">large
        <div id="wf_settings_font">Font Size</div>
      </div><br><br><br>
      
       <input type="button" value="next" id="ses_wordfetch"></center>
    </div>
  <div id="ses_image" style="border:1px dotted gray;display:none;  width:400px; position:relative;height:300px; margin:0px auto;">
      
      <?php
              
      ?>
      <center><b>Brain jogging's Eye Movement</b></center>
      <br><br>
      Select a Image for Eye movement:
      <br><br>
      <center>
       <span>Iimage Lists :</span>
       <select id="eye_imagelist">        
        <option value="0">-Select-</option>
        <?php
        
        foreach ($im as $cat => $wlist){
          if(count($wlist['childs']) > 0){
            
            foreach ($wlist['childs'] as $wl){
             printf('<option value="%s">%s</option>',$wl['filepath'], $wl['title']);
            }
            print "</optgroup>";
          }
        }
        ?>
       </select>
       
         
      <br><br><br>
       <input type="button" value="next" id="ses_imagefetch"></center>
    </div>
 <div id="em_speed" style="display:none;">
      Enter  A Speed (1-9):<input type="text" name="speed" id="speed" maxlength="1"  style="background-color:gray;"><br>
      <center>
      <input type="button" value="Begin" id="em_begin">
      </center>
    </div>
  <div id="em_instuct" style="border:1px dotted gray; display:none; width:400px;padding:10px;font-size:15px;text-align:justify; position:relative;height:300px; margin:0px auto;">
      <center><b>Direction for Eye Movemnt</b></center><br>
      A word or phrase or Image will be flahed  to the right and left sides of the screen. The words to be clled aloud are the first word on the far left and the last
      word on the far right. Students should say the word on the far left. Spell the word,
      and say the word again. Do the same with the word on the far right.<br>
      If is important that you say the word aloud and not silently in your mind student must
      also keep their head still and more theri eyes left to right.<br>
      Click "Next" button below to begin exercise.<br><br>
      <center> <input type="button" value="next" id="em_word_start"></center>
    </div>
  <?php }?>
  <!-- Eye movement End -->
</div>


