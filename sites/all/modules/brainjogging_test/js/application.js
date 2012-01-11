BrianJogging = {};

// Word flash
BrianJogging.wordflash = (function(pub) {
  pub.initialize = function(){
    words = [];  
    wf = {};
    results = {};
    results.status = {};
    results.status.correct = results.status.wrong = 0;
    results.levels = [];
    wf.level = wf.attempts = 1;
    $('#words_flash_div').show();
    showSetting();
  };
  
  showSetting = function(){
    $('#wf_settings').slideDown('slow');
    $('input[name="wf_settings_fsize"]').each(function(index) {
      $(this).click(function() {
      $('#wf_settings_font').css('font-size', $(this).val());
      });
    });
    $('#wf_settings_ok').click(function(){      
      wf.ftype = $('input[name="wf_settings_type"]:checked').val();
      wf.ftype_text = $('input[name="wf_settings_type"]:checked').parent().text();
      wf.wordlist = $('#wf_settings_wl option:selected').val();
      wf.fsize = $('input[name="wf_settings_fsize"]:checked').val();
      if(wf.wordlist == 0){
        alert("Please select any Word list");
        return false;
      }else{
        $.getJSON('/brainjogging/ajax/word_flash/' + wf.wordlist, function(data) {
          words = data.words;
          $('#wf_instruction > p').text(data.instruction);
          $('#wf_settings').slideUp('slow',function(){
            $('#wf_instruction').slideDown('slow');
          });
        });
      }      
      return true;
    });
    
    $('#wf_instruction_ok').click(function(){
      $('#wf_instruction').slideUp('slow', function(){
      $('#wf_begin').show();
      });      
    });
    
    $('#wf_begin_ok').click(function(){
      beginExercise();
    });
    
  };
  
  beginExercise = function(){
    $('#wf_container').html('<div style="margin:0 auto;text-align:center;color:#fff;font-weight:bold;">Level '+ wf.level +'</div><div id="wf_words"></div><br><div id="wf_ans_div"><input type="text" class="wf_answer" size="50" id="wf_answer"></div>');
    $('#wf_words').text(words.slice(((wf.level - 1) * wf.ftype), (wf.level * wf.ftype)).join(" "));
    $('#wf_words').css('font-size', wf.fsize);
    $('#wf_ans_div').hide();
    
    // If first level hide the begin and show exercise
    if(wf.level == 1){
      $('#wf_begin').slideUp('slow', function(){
        $('#wf_container').slideDown();
        
      });  
    }
    
    $.after((5000 - (250 * (wf.level -1))),function(){
      $('#wf_words').slideUp('slow', function(){
        $('#wf_ans_div').show();
        $('#wf_answer').focus(); 
      });
    });
    
    $('#wf_answer').keydown(function(e){
     if(e.which == 13){
      submitResult();
     }
     return true;
    });    
  };
  
  submitResult = function(){
    if($('#wf_words').text().toLowerCase() == $('#wf_answer').val().toLowerCase()){
    $('#wf_container').html('<span class="msg">Anwer Correct..</span>');    
    results.status.correct += 1; 
    if(wf.level < 20){
     $.after(2000,function(){      
      wf.level += 1;      
      beginExercise();
     });
    }
   }else{
    results.levels[wf.attempts] = {}
    results.levels[wf.attempts].question = $('#wf_words').text();
    results.levels[wf.attempts].answer = $('#wf_answer').val();
    results.levels[wf.attempts].result = 0;
    results.levels[wf.attempts].level = wf.level;
    $('#wf_container').html('<span class="wrong">Anwer Incorret !!!</span><br><span class="wrong">Try Again...</span>');
    results.status.wrong += 1;
    if(results.status.wrong < 4){
     $.after(2000,function(){
      beginExercise();
     });  
    }    
   }
   
   // Show the Test result 
   if(results.status.wrong == 4  || wf.level == 20){
    $.after(2000,function(){
      showResult();
     
     
    });
   }else{
    wf.attempts++; 
   }
  };
  
  showResult = function(){
    
    var tot_atm=results.status.wrong+results.status.correct;
    results["res"]={res:wf};
    results["pers"]={perecent:Math.ceil((results.status.correct/wf.attempts) * 100 )};
    results["tot_atem"]={tot:tot_atm};
    xmlhttp=$.ajax({
          type: 'POST',
          url: '/brainjogging/wordflash/submit',
          data: 'res='+$.toJSON(results),
          success: function(msg){          
          }
          });
    
  res = '<table border="1" width="100%" cellpadding="0" cellspacing="0">';
  res += '<tr><td align="center" colspan="3">Word Flash - '+ wf.ftype_text +' - Result</td></tr>';
  res += '<tr><td>Name :</td><td colspan="2"> '+Drupal.settings.uname+'</td></tr>';
  res += '<tr><td>Date :</td><td colspan="2"> '+ new Date() +'</td></tr>';
  res += '<tr><td align="center">Attempts</td><td align="center">Success</td><td align="center">Grade</td></tr>';
  res += '<tr><td align="center">'+ wf.attempts +'</td><td align="center">'+ results.status.correct +'</td><td align="center">'+ Math.ceil((results.status.correct/wf.attempts) * 100 ) +'%</td></tr>';
  res += '<tr><td align="center"><input type="button" value="Print" onclick="window.print()"></td>';
  res += '<td align="center"><input id="wf_rl" type="button" value="Repeat Lesson"></td>';
  res += '<td align="center"><input id="wf_mm" type="button" value="Main Menu"></td></tr></table>';
  $('#wf_container').html(res);
  
  $('#wf_rl').click(function(){
    window.location = "/brainjogging/test/word_flash";
  });
  $('#wf_mm').click(function(){
    window.location = "/brainjogging/test/dashboard";
  });
  var per=Math.ceil((results.status.correct/wf.attempts) * 100 );
  var lf_grade_compare=0;
    if(wf.ftype == 2){
     lf_grade_compare = Drupal.settings.wf_two;
    }
     if(wf.ftype == 3){
     lf_grade_compare = Drupal.settings.wf_three;
    }
     if(wf.ftype == 4){
     lf_grade_compare = Drupal.settings.wf_three;
    }
  

  if(lf_grade_compare =="" && per > 50)
   {
    var r=4+parseInt(Math.random()*16);for(var i=r; i--;){setTimeout('createFirework(30,75,6,7,null,null,null,null,Math.random()>0.5,true)',(i+1)*(1+parseInt(Math.random()*1000)));}
    $("#congrats").fadeIn('slow');
    setTimeout(function(){ $("#congrats").fadeOut() }, 5000);
   }
   
  if(per > 50 && per > lf_grade_compare ){
    var r=4+parseInt(Math.random()*16);for(var i=r; i--;){setTimeout('createFirework(30,75,6,7,null,null,null,null,Math.random()>0.5,true)',(i+1)*(1+parseInt(Math.random()*1000)));}
    $("#congrats").fadeIn('slow');
    setTimeout(function(){ $("#congrats").fadeOut() }, 5000);
   }
  
  }
     
     
  return pub;
}(BrianJogging.wordflash || {}));

// Letter flash
BrianJogging.letter_flash = (function(pub) {
  pub.init = {};
  pub.initialize = function(args){
    pub.init = args;
    properties = {
      letter_bank : new Array('a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'),
      Case : 0,
      type : 2,
      f_size : "large",
      time : 5000,
      level : init.level ? init.level : 1,
      sublevel : 1,
      max_attempts : 20,
      total_attempts : 0,
      wrong_attempts : 0,
      correct_attempts : 0,
      qn_array  :new Array(),
      ans_array :new Array(),
      result    :new Array(),
      qn        :new Array(),
      ans       :new Array(),
      pos       :new Array(),
      lev       :new Array(),
      subl      :new Array(),
      r_size    :1,
      bj_lf_test : {},
      ttype  :0
    },
    this.showSetting()
  };
  
  pub.showSetting = function(){
    if(!init.change_case){
      $('#lf_case').remove();
    }
    $('#letter_flash_div').show();    
    $('#lf_description').hide();    //hide the description div
    $('#lf_test_main_container').hide();           //hide the test div
    $('#lf_begin').hide();          //Hide the begun button container
    $('lf_test_container').hide();  //hide the test(chat table) div
    $('#lf_cp').show();             //hide the control panel div
    $('#result_container').hide();            //hide the result_container div
    $('lf_rll_span').hide;   //Initially hide the result table repeat from the same level
    
    //add event to description div button
    $('#desc').click(function(){
      $('#lf_description').hide(); //hide the description div
      $('#lf_test_main_container').show();        //Show the main test div
      $('#lf_begin').show();       //Show the start to begin button
    });
    
    //add event to the begin test button
    $('#lf_begin_test_btn').click(function(){
      $('#lf_begin').hide();         //hide begun test div
      $('lf_test_container').show(); //show test div
      pub.launchLetterFlash();         //start the test
    });
    
    /**
     * Control Panel events
     */
    //add event to the case selection radios
    $("input:radio[name=case]").click(function() {
      properties.Case = $(this).val();
    });
    
    //add event to the test type selection radios
    $("input:radio[name=type]").click(function() {
      properties.type = $(this).val();
    });
    
    //add event to the font size selection radios
    $("input:radio[name=f_size]").click(function() {
      properties.f_size = $(this).val();
    });
    
    //add events to the control panel div button
    $('#start_lf').click(function(){
      $('#lf_cp').slideUp("slow");           //hide the cpanel div
      $('#lf_description').show();  //show the descriotion div
    });
    
    //assign empty objects to the first level tests
    properties.bj_lf_test[properties.level] = {};
    properties.bj_lf_test[properties.level][properties.sublevel] = {};
  };
  
  pub.launchLetterFlash = function(){
    var l = "";
    var letters = [];
    
    //remove the previos test if there.
    //Technically remove the previous
    //test table element
    $('#test_table').remove();
    
    //Prepare the charecters to be shown for test
    properties.qn_array = new Array();
    reinforcement_time = Math.ceil(20 *(init.missed_letter_reinforcement/100));
    for(i=0; i < properties.type; i++){
      l = properties.letter_bank[Math.ceil(Math.random()*25)];
      if($.inArray(l,properties.qn_array) == -1){
        letters[i] = {id:i,charecter:properties.Case? l.toUpperCase() : l,size : properties.f_size,tabindex:i+1};
        properties.qn_array.push(l);
      }
    }
    var context = {
      letter : letters
    };
    
    //create the html for the test
    var source   = $("#template-letter-flash").html();
    var template = Handlebars.compile(source);
    var html = template(context);
    
    $('#lf_test_container').append(html);
    
    //first hide the char <span> for a while
    $('span[id^=test_char_span_]').hide();
    
    //make chat <td> beckground to yellow
    $('#chars > td').css("background-color","yellow");
    
    //first hide the inputs
    $('#inputs').hide();
    
    //show yelow background to the user for 2 seconds
    //after show the test
    $.after(0.5, "second", function() {
      pub.showTest();
    });
  }
  
  //Start the test
  pub.showTest = function(){
    //apply white backgrounf while show the chars
    $('#chars > td').css("background-color","white");
    
    //show the char appering places to the user
    $('span[id^=test_char_span_]').show();
    
    //apply the events after the time delay
    $.after(properties.time, function() {
      //HIde the charecters
      $('span[id^=test_char_span_]').hide();
      
      //show the textboxes
      $('#inputs').show();
      
      //set the focus to the first textbox
      $('#test_input_0').focus();
    });
    
    //add KeyUp events to the input boxes
    properties.ans_array = new Array();
    $('input[name^=test_input_]').each(function(){
      $(this).keyup(function(){
        test_ans_lettes = new Array();
        var str = $(this).attr('id');
        
        if($(this).attr('id') != 'test_input_'+ (properties.type - 1)){
          //move the focus to the next textbox
          $('#test_input_'+ ((Number(str.substr(str.length-1)) + 1))).focus();
          
          //add the ans char into the array
          properties.ans_array.push($(this).val());
          //Disable the current textbox
          $(this).attr('disabled','disabled');
        }
        else{
          //add the ans char into the array
          properties.ans_array.push($(this).val());
          //Disable the current textbox
          $(this).attr('disabled','disabled');
          
          pub.computeResults();
        }
      });
    });
  }
 
  pub.computeResults = function(){
    //Increase the total No of attempts
    properties.total_attempts++;
    properties.bj_lf_test[properties.level][properties.sublevel] = {qn_chars:properties.qn_array,ans_chars:properties.ans_array};
    properties.bj_lf_test['type']=[properties.type];
    var level_flag = true;
    for(i=0; i < properties.type; i++){
      //compare qn chars against ans chars
      
      
      if(properties.ans_array[i] != properties.qn_array[i]){
        if(properties.type==2){
        if(i==0){var pos=1}
        if(i==1){var pos=2}
        }
        if(properties.type==3){
        if(i==0){var pos=1}
        if(i==1){var pos=3}
        if(i==2){var pos=2}
        }
        if(properties.type==4){
        if(i==0){var pos=1}
        if(i==1){var pos=4}
        if(i==2){var pos=5}
        if(i==3){var pos=2}
        }
        
       properties.lev[properties.r_size]  = properties.level;
       properties.subl[properties.r_size] = properties.sublevel;
       properties.qn[properties.r_size]   = properties.qn_array[i];
       properties.ans[properties.r_size]  = properties.ans_array[i];
       properties.pos[properties.r_size]  = pos;
      
        properties.r_size++;
        level_flag = false;
      }
    }
    
    //if answers are correct
    if(level_flag){
      //if total 20 levels complited
      if(properties.level == 21){
        pub.quitAndShowResult();    //quit the test and show the results
      }
      else{ //if level is lessthen 20
        if(properties.level == (init.highest_level - 1) && (init.highest_level - 1) != 0){
          alert("Congrats... Achived the highest Level");
        }
        else{
          alert("Congrats.. You successfully complete Level - " + properties.level);
        }
        properties.sublevel = 1;                         //initiate the sublevel to 1 for the next level test
        properties.time = properties.time - 250;         //Decrease the time level 250 ms for the next level test
        properties.correct_attempts++;                   //Increase the correct attempts
        properties.level++;                              //Increase the level of the exam
        properties.bj_lf_test[properties.level] = {};    //Declare object for the next level
        pub.launchLetterFlash();                           //Start the next level exam
      }
    }
    else{ //if the answer is not correct
      if(properties.sublevel == 3){
        
        properties.bj_lf_test['result']={lev:properties.lev,subl:properties.subl,qn:properties.qn,ans:properties.ans,pos:properties.pos};
        pub.quitAndShowResult();
        //quit and show the result
          
          
      }
      else{
        alert("InCorrect.... Try again");
        properties.wrong_attempts++;                                       //increase the wrong attempts
        properties.sublevel++;                                             //increase the sublevel
        properties.bj_lf_test[properties.level][properties.sublevel] = {}; //Declare object for the empty level
        pub.launchLetterFlash();                                             //Start the new test
      }
    }
  }
  
  pub.quitAndShowResult = function(){
  
    //remove the test.
    //Technically remove the previous
    //test table element
    $('#test_table').remove();
    
    show_same_level = Math.ceil(20 * (init.show_start_from_same_level/100));
    if(show_same_level < (properties.level)){
      init.level = properties.level - 1;
      $('lf_rll_span').show();
      $('#lf_rll').click(function(){
        pub.initialize(init);
      });
    }
    
    //set the total attempts value
    $('#attempts').text(properties.total_attempts);
    //sett he correct attempts value
    $('#correct').text((properties.correct_attempts ? properties.correct_attempts : '0' ));
    //Set the grade
    $('#grade').text(Math.ceil(((properties.correct_attempts/properties.total_attempts) * 100)) +  '%');
    //set the highest level achived
    $('#level').text(((properties.level - 1) ? (properties.level - 1) : '0'));

    var correct=(properties.correct_attempts ? properties.correct_attempts : '0' )
    var grade =(Math.ceil(((properties.correct_attempts/properties.total_attempts) * 100)) );
    var level =(((properties.level - 1) ? (properties.level - 1) : '0'));
    var type  =properties.type;
    properties.bj_lf_test['res']={t_at:properties.total_attempts,c_at:correct,level:level,grade:grade};
    xmlhttp=$.ajax({
          type: 'POST',
          url: '/brainjogging/letterflash/submit/',
          data: 'res='+$.toJSON(properties.bj_lf_test),
          success: function(msg){}
          });
          
     $('#lf_rl').click(function(){
     pub.initialize(init);
    });
    
    $('#lf_mm').click(function(){
      window.location = "/brainjogging/test/dashboard";
    });
    
    var lf_grade_compare=0;
    if(type == 2){
     lf_grade_compare = Drupal.settings.lf_two;
    }
     if(type == 3){
     lf_grade_compare = Drupal.settings.lf_three;
    }
     if(type == 4){
     lf_grade_compare = Drupal.settings.lf_three;
    }
     
  $('#result_container').show();
   if(lf_grade_compare =="" && grade > 50)
   {
    var r=4+parseInt(Math.random()*16);for(var i=r; i--;){setTimeout('createFirework(30,75,6,7,null,null,null,null,Math.random()>0.5,true)',(i+1)*(1+parseInt(Math.random()*1000)));}
    $("#congrats").fadeIn('slow');
    setTimeout(function(){ $("#congrats").fadeOut() }, 5000);
   }
   
  if(grade > 50 && grade > lf_grade_compare ){
    var r=4+parseInt(Math.random()*16);for(var i=r; i--;){setTimeout('createFirework(30,75,6,7,null,null,null,null,Math.random()>0.5,true)',(i+1)*(1+parseInt(Math.random()*1000)));}
    $("#congrats").fadeIn('slow');
    setTimeout(function(){ $("#congrats").fadeOut() }, 5000);
   }
    
    
    //show the results
    
    
    //$('#letter_flash_div').children().each(function(){
    //  $(this).remove(); 
    //});
  }
  
  return pub;
}(BrianJogging.letter_flash || {}));


BrianJogging.eyemomvent = (function(pub) {
    pub.initialize = function(){        
        $('#header').hide();
        $('#admin-menu').hide();
        $('#eye_moment').show();
        $('input[name="wf_settings_fsize"]').each(function(index) {
      $(this).click(function() {
        $('#wf_settings_font').css('font-size', $(this).val());
        $('#em_letter').css('font-size', $(this).val());
        
      });
    });
        
        em_pos1     = 0;
        em_max      = 500;
        em_tip_top  = 0;
        em_count    = 0;
        em_sp       = 3000;
        em_loop     = 1;
        speed       = 0;
        res         = new Array();
        em_option   = 0;
        em_imcount  = 0;
        bj_eye_move = {};
        
        
        bj_eye_move['res']=Drupal.settings.wordlist_id;
        em_input=Drupal.settings.input1;
        
        $('#ses_wordfetch').click(function(){
          
          
          var eye_list=$('#eye_wordlist').val();
         
          if(eye_list==0){
            alert("select the word lilst");
            return false;
          }
          else{
          bj_eye_move.wordlist = $('#eye_wordlist option:selected').val();
          $.getJSON('/brainjogging/ajax/eye_movement/' + bj_eye_move.wordlist, function(data) {
          em_input = data.words;
         
        });
          }
          pub.eye_word_next();  
      return true;
         
          
    });
         $('#ses_imagefetch').click(function(){
          
          
          var eye_imlist=$('#eye_imagelist').val();
         
          if(eye_imlist==0){
            alert("select the Image lilst");
            return false;
          }
          else{
          bj_eye_move.wordlist = $('#eye_imagelist option:selected').val();
         
          
        
              em_input = "<img src='/"+bj_eye_move.wordlist+"'/>";
              em_option = 1;
          }
          pub.eye_word_next();  
      return true;
         
          
    });
        $('#em_main').click(function(){
          $('#eye_moment').hide();
          window.location = "/brainjogging/test/dashboard/emset";
        });
         $('#ses_next').click(function(){
        var eye_option = $('#option_eyemove').val();
        
         $('#ses_menu').hide();
        if(eye_option == 'Eye Movement Activity'){
         $('#ses_wordlist').slideDown('slow');
        }
        else{
          $('#ses_image').slideDown('slow');
        }
         
        });
        $('#speed').keypress(function(evt){
          
         var charCode = (evt.which) ? evt.which : event.keyCode
         if (charCode > 31 && (charCode < 48 || charCode > 57)) {
            
            return false;
         }
         return true;
        });
        $('#em_next').click(function(){
         pub.em_next();
         //pub.em_speed();
        });
         $('#em_next1').click(function(){
         
         pub.em_next1();
         
        });
        $('#em_begin').click(function(){
          pub.em_speed1();  
        });
        $('#em_start').click(function(){
            pub.em_speed(); 
          pub.em_start();  
        });
        $('#em_word_start').click(function(){
            
          pub.em_word_start();  
        });
        $('#em_init').slideDown('slow');
    }
    
    pub.em_flash = function() {
      
       $('#em_move').html(em_input[em_count]);
       var em_end =screen.width;
       em_pos1 += em_end-210;
       if (em_count==0) {
          em_pos1=0;
        }
       if (em_pos1 > em_end) {
           em_pos1 = 0;
        }
      
       
         if(em_tip_top<em_max) {
          em_tip_top+=50;
          }
          else{
          em_tip_top=20;
          }
       
       if(em_count==em_input.length) {
       
       if(em_loop==1)
       {
         alert("first eye test end");
         
       bj_eye_move['res1']=Drupal.settings.wordlist_id1;
          em_input=Drupal.settings.input2;
          em_loop++;
          em_count=0;
          em_tip_top=0;
          pub.em_count();
          return false;
           
       }
       if(em_loop==2)
       {
         alert("Scecond eye test end");
          
        bj_eye_move['res2']=Drupal.settings.wordlist_id2;
         em_input=Drupal.settings.input3;
         em_loop++;
          em_count=0;
          em_tip_top=0;
         pub.em_count();
         return false;
         
           
       }
         if(em_loop==3)
          {            
          xmlhttp=$.ajax({
          type: 'POST',
          url: '/brainjogging/eye_movement/submit',
          data: 'res='+$.toJSON(bj_eye_move)+'&speed='+speed,
          success:function(){
                    }
          });
                  
          window.location='/brainjogging/test/dashboard/emset';
          return true;
          }
        
          em_loop++;
          em_count=0;
          em_tip_top=0;
          
          pub.em_speed();
          return false;
       
        }
      
       if(em_pos1 == 0){
        $("#em_letter").css("right", ''); 
        $("#em_letter").css("left", '0px');        
       }else{
        $("#em_letter").css("left", ''); 
        $("#em_letter").css("right", '0px')
       }
       $("#em_letter").css("top", em_tip_top);
       $.after(em_sp,function(){
        pub.em_flash();
        });
       em_count++;
       return true;
    }
    
  pub.em_flash1 = function() {
    if(em_option == 0){
       $('#em_move').html(em_input[em_count]);
    }
    else{
      em_max = 400;
       $('#em_move').html(em_input);
    }
       var em_end =screen.width;
       em_pos1 += em_end-210;
       if (em_count==0) {
          em_pos1=0;
        }
       if (em_pos1 > em_end) {
           em_pos1 = 0;
        }
       if(em_count%2==0) { 
         if(em_tip_top<em_max) {
          em_tip_top+=50;
          }
          else{
          em_tip_top=20;
          }
        }
       if(em_count==em_input.length || em_imcount == 25) {
         if(em_loop==1)
          {            
          xmlhttp=$.ajax({
          type: 'POST',
          url: '/brainjogging/eye_movement/submit',
          data: 'res='+$.toJSON(bj_eye_move)+'&speed='+speed,
          success :function(){         }
          
          });
          
         window.location='/brainjogging/test/dashboard/emset';
           return true;
          }
        
          em_loop++;
          em_count=0;
          em_tip_top=0;
          
          pub.em_speed1();
          return false;
        }
       if(em_pos1 == 0){
        $("#em_letter").css("right", ''); 
        $("#em_letter").css("left", '0px');        
       }else{
        $("#em_letter").css("left", ''); 
        $("#em_letter").css("right", '0px');
       }
       $("#em_letter").css("top", em_tip_top);
       $.after(em_sp,function(){
        pub.em_flash1();
        });
       em_count++;
       if(em_option == 1){
       em_imcount++;
       }
       return true;
    }
    
    pub.em_next = function() {
        $('#em_init').hide()
        $('#em_instuct').slideDown('slow');
        $('#em_speed').show();
        $('#em_speed').css("position",'relative');
        $('#em_speed').css("width",500);
        $('#em_speed').css("margin",'0px auto');
    }
      pub.em_next1 = function() {
        
        $('#em_init').css("display",'none');
        $('#em_speed').css("display","block");
        $('#em_speed').show();
        $('#em_speed').css("position",'relative');
        $('#em_speed').css("width",500);
        $('#em_speed').css("margin",'0px auto');
    }
      pub.eye_word_next = function() {
        
        $('#ses_wordlist').css("display",'none');
         $('#ses_image').css("display",'none');
        $('#em_speed').css("display","block");
        $('#em_speed').show();
        $('#em_speed').css("position",'relative');
        $('#em_speed').css("width",500);
        $('#em_speed').css("margin",'0px auto');
    }
     
     pub.em_count = function() {
       if(em_loop==1){
        $('#eyecount').text("Three");
        }
        if(em_loop==2){
        $('#eyecount').text("Two More ");
        }
        if(em_loop==3){
        $('#eyecount').text("Final");
        }
        $('#em_move').css("display","none");
        $('#em_init').css("display",'block');
    }
     
    pub.em_speed = function() {
       //var em_spe=$('#speed').val();
      if(em_loop==1){
        $('#eyecount').text("Three");
        }
        if(em_loop==2){
        $('#eyecount').text("Two More ");
        }
        if(em_loop==3){
        $('#eyecount').text("Final");
        }
        $('#em_init').css("display",'none');
       var em_spe=9;
       if(em_spe.length==0) {
         alert("Enter the speed");
        }
       else{
        speed=em_spe;
            $('#em_speed').css("display","none");
            $('#em_instuct').css("display","block");
             $('#em_move').css("display","none");
            
            if(em_loop==1)
            {
            em_sp = em_sp/em_spe;
            }
        }
       
    }
     pub.em_speed1 = function() {
       var em_spe=$('#speed').val();
        $('#em_init').css("display",'none');
       //var em_spe=9;
       if(em_spe.length==0) {
         alert("Enter the speed");
        }
       else{
        speed=em_spe;
            $('#em_speed').css("display","none");
            $('#em_instuct').css("display","block");
             $('#em_move').css("display","none");
            em_sp = em_sp/em_spe;
        }
       
    }
    pub.em_start = function() {
        $('#em_instuct').css("display","none");
        $('#em_move').css("display","block");
        pub.em_flash(); 
    }
     pub.em_word_start = function() {
        $('#em_instuct').css("display","none");
        $('#em_move').css("display","block");
        pub.em_flash1(); 
    }
   
    
  return pub;
}(BrianJogging.eyemomvent || {}));
