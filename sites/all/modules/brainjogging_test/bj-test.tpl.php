<div id="container">
  <div id="main_menu">
    <ul>
      <li><a class="letter" href="javascript://"><img src="/<?php echo $vars['path']; ?>/img/brain-arrow.png">Letter Flash</a></li>
      <li><a class="word" href="javascript://"><img src="/<?php echo $vars['path']; ?>/img/brain-arrow.png">Word Flash</a></li>
      <li><a class="eye" href="javascript://"><img src="/<?php echo $vars['path']; ?>/img/brain-arrow.png">Eye Movement Text</a></li>
      </ul>
  </div>
  
  <!-- Words flash starts -->
  <div id="words_flash_div" style="display:none">
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
        <option value="1">Fruits</option>
        <option disabled="disabled" value="2">Adverbs</option>
        <option disabled="disabled" value="3">Adjectives</option>
        <option disabled="disabled" value="4">Games</option>          
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
  <!-- Words flash ends -->
  
  
  <div id="letter_flash_div" style="display:none">
    <!-- Letter Flash Control Panel -->
    <div id="lf_cp">
      <table>
        <tr>
          <td>
            Select Case : 
          </td>
          <td>
            <input type="radio" name="case" value="0" checked="checked" /> Lowercase<br>
            <input type="radio" name="case" value="1" /> Upper Case
          </td>
        </tr>
        <tr>
          <td>
            Select Test type : 
          </td>
          <td>
            <input type="radio" name="type" value="2" checked="checked" /> 2 Letter Flash<br>
            <input type="radio" name="type" value="3" /> 3 Letter Flash <br>
            <input type="radio" name="type" value="4" /> 4 Letter Flash <br>
          </td>
        </tr>
        <tr>
          <td>
            Select Font Size : 
          </td>
          <td>
            <input type="radio" name="f_size" value="small" /> Small<br>
            <input type="radio" name="f_size" value="medium" /> Medium <br>
            <input type="radio" name="f_size" value="large" checked="checked" /> Large<br>
          </td>
        </tr>
        <tr>
          <td colspan="2" align="center">
            <input type="button" id="start_lf" name="start_lf" value="Click to start test" /> 
          </td>
        </tr>
      </table>
    </div>
    <!-- Letter Flash Control Panel -->
    <div id="lf_description" style="width:400px;margin:0 auto;">
      <span>
        <p>Letter Flash  instructions will come here....
        </p>
        <input type="button" id="desc" name="desc" value="Click to start test" /> 
      </span>
    </div>
    
    <!-- Letter Flash Control Panel -->
    <div id="lf_test_main_container">
      <div id="lf_begin">
        <input type="button" id="lf_begin_test_btn" name="lf_begin_test_btn" value="Click to begin test" /> 
      </div>
      <div id="lf_test_container">
        
      </div>
    </div>
  </div>
  <div id="result_container" style="display:none">
    <table border="1" cellpadding="0" cellspacing="0">
      <tr>
        <th>Attempts</th>
        <th>Correct</th>
        <th>Grade</th>
        <th>High Level</th>
      </tr>
      <tr>
        <td align="center"><span id="attempts"></span></td>
        <td align="center"><span id="correct"></span></td>
        <td align="center"><span id="grade"></span></td>
        <td align="center"><span id="level"></span></td>
      </tr>
      <tr>
        <td align="center"><input type="button" value="Print" onclick="window.print()"></td>
        <td colspan="2" align="center"><input id="lf_rl" type="button" value="Repeat Lesson"></td>
        <td align="center"><input id="lf_mm" type="button" value="Main Menu"></td>          
      </tr>
    </table>
  </div>
  <!-- Letter flash ends -->
  
  <!-- Eye movement Start-->
  <div id="eye_moment" style="width:100%; margin:10%  auto; position:relative;display:none">
    <div id="em_letter" style="position:absolute;">
      <span id="em_move"> </span>
    </div>
    <div id="em_init" style="border:1px dotted gray; width:400px; position:relative;height:300px; margin:0px auto; display:none;">
      <center><b> Brain jogging's Eye Movement<br/>
      Exercise</b></center><br/><br/>
      Welcome to  brain Jogging. You must complete three
      Eye Movement activities before useing any other activities.
      You will now be directed to the Eye Movement activity.
      <br/><br/>
      <center>
      <input type="button" value="Return to Main" id="em_main">
      <input type="button" value="Next" id="em_next">
      </center>
    </div>
    <div id="em_speed" style="display:none;">
      Enter  A Speed (1-9):<input type="text" name="speed" id="speed" maxlength="1"  style="background-color:gray;"><br>
      <center>
      <input type="button" value="Begin" id="em_begin">
      </center>
    </div>
    <div id="em_instuct" style="border:1px dotted gray; display:none; width:400px; position:relative;height:300px; margin:0px auto;">
      <center><b>Direction for Eye Movemnt</b></center>
      A word or phrase will be flahed  to the right and left sides of the screen. The words to be clled aloud are the first word on the far left and the last
      word on the far right. Students should say the word on the far left. Spell the word,
      and say the word again. Do the same with the word on the far right.<br>
      If is important that you say the word aloud and not silently in your mind student must
      also keep their head still and more theri eyes left to right.<br>
      Click "Next" button below to begin exercise.<br>
      <center> <input type="button" value="next" id="em_start"></center>
    </div>
  </div>
  <!-- Eye movement End -->
</div>
 <script id="template-letter-flash" type="text/x-handlebars-template">
  <table id="test_table" align="center" width="40%">
    <tr id="chars">
      {{#each letter}}
      <td align="center">
        <div class="chars" id="test_char_{{id}}"><span id="test_char_span_{{id}}" class="{{size}}">{{charecter}}</span></div>
      </td>
      {{/each}}
    </tr>
    <tr id="inputs">
      {{#each letter}}
      <td align="center">
        <div id="test_text_{{id}}" class="chars"><input type="text" name="test_input_{{id}}" id="test_input_{{id}}" size="5" maxlength="1" tabindex="{{tabindex}}"></div>
      </td>
      {{/each}}
    </tr>
  </table>
</script>


