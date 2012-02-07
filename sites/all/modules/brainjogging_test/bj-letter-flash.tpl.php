<div id="container">
  
  
<div id="fireworks-template">
 <div id="fw" class="firework"></div>
 <div id="fp" class="fireworkParticle"><img src="/<?php echo $vars['path']; ?>/img/rainbow.gif" alt="" /></div>
</div>

<div id="fireContainer"></div>


  
  <div id="letter_flash_div" style="display:none">
    <!-- Letter Flash Control Panel -->
    <div id="lf_cp">
      <table id="letter_set" >
        <td colspan="2" align="center" style="font-weight:bold;"> Letter Flash </td><tr>
        <tr id="lf_case">
          
          <td style="font-weight:bold;">
            Select Case : 
          </td>
          <td>
            <input type="radio" name="case" value="0" checked="checked" /> Lowercase<br>
            <input type="radio" name="case" value="1" /> Upper Case
          </td>
        </tr>
        <tr id="lf_type">
          <td style="font-weight:bold;">
            Select Test type : 
          </td>
          <td>
            <input type="radio" name="type" value="2" checked="checked" /> 2 Letter Flash<br>
            <input type="radio" name="type" value="3" /> 3 Letter Flash <br>
            <input type="radio" name="type" value="4" /> 4 Letter Flash <br>
          </td>
        </tr>
        <tr id="lf_font_type">
          <td style="font-weight:bold;">
            Select Font Size : 
          </td>
          <td>
            <input type="radio" name="f_size" value="small" /> Small<br>
            <input type="radio" name="f_size" value="medium" /> Medium <br>
            <input type="radio" name="f_size" value="large" checked="checked" /> Large<br>
          </td>
        </tr>
        <tr style="height:120px">
          <td colspan="2" align="center">
            <div id="sample_letter" style="text-align:center" ></div> 
          </td>
        </tr>
        <tr>
          <td colspan="2" align="center">
            <input type="button" id="start_lf" name="start_lf" value="Next" /> 
          </td>
        </tr>
      </table>
    </div>
    <!-- Letter Flash Control Panel -->
    <div id="lf_description" style="width:400px;margin:0 auto;">
      <span>
        <p><center><h3><b>Direction for Letter Flash</b></h3></center><br>
        A group of letters will be flashed in the center of the screen
        . The student must say the letters aloud while looking at the screen BEFORE
       he/she looks down at the keyboard. Repeat the letters aloud again while typing <br>
       <br>
       It is important  that you say the letters aloud and not silently in your mind<br>
       
       <center>Click "NEXT" button bellow to begin exercise</center>
       
       
        </p><br>
        <center><input type="button" id="desc" name="desc" value="Next" /> </center>
      </span>
    </div>
    
    <!-- Letter Flash Control Panel -->
    <div id="lf_test_main_container">
      <div id="lf_test_container">
        <table id="test_table" align="center">
         <tbody id="lf_test_tbody">
          <tr id="lf_test_first"><td align="center" id="lf_test_head" ><span style="font-size:15px;letter-spacing:2px;">Camp Acadamia's Letter Flash</span><br><br><span style="font-size:16px; letter-spacing:2px; font-weight:bold;">Click Next to begin</span><br><br><br><br></td></tr>
          <tr id="lf_test_second"><td id="but" align="center"><input type="button" id="lf_begin_test_btn" name="lf_begin_test_btn" value="Next" /> </td></tr>
         </tbody>
        </table>
      </div>
    </div>
  </div>
  <div id="result_container" style="display:none">
    <table border="1"  id="letter_res" cellpadding="0" cellspacing="0">
      <td align="center" colspan="4" style="font-weight:bold;">Letter Flash Result</td><tr>
      <td colspan="2">Name</td>
      <td colspan="2">
        <?php global $user; echo $user->profile_first_name; ?>
        </td>
      <tr>
      <td colspan="2">Date</td>
      <td colspan="2"><?php echo  Date('Y-m-d'); ?></td>
      <tr>
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
        <td colspan="2" align="center"><span><input id="lf_rl" type="button" value="Repeat Lesson"></span><span id="lf_rll_span"><input id="lf_rll" type="button" value="Repeat from the last level"></span></td>
        <td align="center"><input id="lf_mm" type="button" value="Main Menu"></td>          
      </tr>
    </table>
  </div>
  <div id="lf_result">
    <table id="test_table_result" align="center">
      <tr><td align="center" id="head">Error</td></tr>
    </table>
  </div>
  <div id="congrats" style="display:none;width:400px; margin:0 auto">
    <img src="/<?php echo $vars['path']; ?>/img/gold.gif">
  </div>
  <!-- Letter flash ends -->
</div>
<script id="template-letter-flash" type="text/x-handlebars-template">
  <tr id="chars">
    {{#each letter}}
    <td align="center">
      <div class="chars" id="test_char_{{id}}" style="border-bottom:1px solid"><span id="test_char_span_{{id}}" class="{{size}}">{{charecter}}</span></div>
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
</script>

<script id="template-letter-flash-result-failure" type="text/x-handlebars-template">
  <tr id="res_error" align="center"><td>Level &nbsp;<span id='lf_level'> </span><br><b>Answer Incorrect!</b> <br><br><br><br></td></td>
  <tr>
  <tr id="input_chars">
    {{#each qn}}
    <td align="center">
      <div class="chars"><span class="{{size}}">{{this}}</span></div>
    </td>
    {{/each}}
  </tr>
  <tr id="ans_chars">
    {{#each ans}}
    <td align="center">
      <div class="chars"><span class="{{size}}">{{this}}</span></div>
    </td>
    {{/each}}
  </tr>
</script>

<script id="template-letter-flash-result-success" type="text/x-handlebars-template">
  <tr id="res_error" align="center"><td>Level &nbsp; {{leval}}<br> <b>Answer Correct!</b></td></td>
  <tr id="input_chars">
    {{#each qn}}
    <td align="center">
      <div class="chars"><span class="{{size}}">{{this}}</span></div>
    </td>
    {{/each}}
  </tr>
  <tr id="ans_chars">
    {{#each ans}}
    <td align="center">
      <div class="chars"><span class="{{size}}">{{this}}</span></div>
    </td>
    {{/each}}
  </tr>
</script>

<script id="template-letter-flash-start" type="text/x-handlebars-template">
  <tr>
    {{#each letter}}
    <td align="center">
      <div class="chars" style="border-bottom:1px solid"><span class="{{size}}">{{charecter}}</span></div>
    </td>
    {{/each}}
  </tr>
</script>


