//
$(document).ready(function() {
  $('a').each(function(index) {
    if($(this).text().toLowerCase() == 'edit'){
      $(this).addClass('icon');
      $(this).addClass('edit');
    }else if($(this).text().toLowerCase() == 'delete'){
      $(this).addClass('icon');
      $(this).addClass('delete');
    }
  });  
});