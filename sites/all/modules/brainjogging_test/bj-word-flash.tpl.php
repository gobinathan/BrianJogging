<div id="container">
  <!-- Words flash starts -->
  <div id="fireworks-template">
 <div id="fw" class="firework"></div>
 <div id="fp" class="fireworkParticle"><img src="/<?php echo $varpath['path']; ?>/img/rainbow.gif" alt="" /></div>
</div>

<div id="fireContainer"></div>

  <div id="words_flash_div" style="display:none">
    <div id="wf_heading">Camp Acadamia's Word Flash </div>
    <div id="wf_settings" style="display:none">
      <div>
        <span style="display:block;margin:0 auto;text-align:center;color:#fff"> Word Flash Settings </span>
        <span>Type :</span>
        <ul>
          <li><input type="radio" checked="checked" name="wf_settings_type" value="2"> Two Words Flash </li>
          <li><input type="radio" name="wf_settings_type" value="3"> Three Words Flash </li>
          <li><input type="radio" name="wf_settings_type" value="4"> Four Words Flash </li>
        </ul>
      </div>
      <div>
       <span>Word Lists :</span>
       <select id="wf_settings_wl">        
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
      </div>
      <div>
        <span>Font Size :</span>
        <input type="radio" name="wf_settings_fsize" value="small">Small
        <input type="radio" name="wf_settings_fsize" checked="checked" value="medium">Medium
        <input type="radio" name="wf_settings_fsize" value="large">large
        <div id="wf_settings_font">Font Size</div>
      </div>
      <input type="button" id="wf_settings_ok" value="OK">
    </div>
  
    <div id="wf_instruction" style="display:none">
      <span>Word flash instruction</span>
      <p> Word flash instructions will come here....</p>
      <input type="button" id="wf_instruction_ok" value="OK">
    </div>
  
    <div id="wf_begin" style="display:none">
      <div>Click Next to Begin</div><br>
      <div><input type="button" id="wf_begin_ok" value="Next"></div>
    </div>
  
    <div id="wf_container" style="display:none">
      <div id="wf_words"></div><br>
      <div><input type="text" size="50" id="wf_answer"></div>
    </div>
  </div>
  
  <div id="congrats" style="display:none;width:400px; margin:0 auto">
    <img src="/<?php echo $varpath['path']; ?>/img/gold.gif">
  </div>
  <!-- Words flash ends -->
 </div>