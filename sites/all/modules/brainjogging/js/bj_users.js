$(document).ready(function() {
	toggle_parent_fields();
  $('#edit-roles').change(function(){
		toggle_parent_fields();
	});
});

function toggle_parent_fields(){
	$('#edit-teacher-wrapper').children('label').children('span').remove();
	$('#edit-parent-fname-wrapper').children('label').children('span').remove();
	$('#edit-parent-lname-wrapper').children('label').children('span').remove();
	$('#edit-parent-mail-wrapper').children('label').children('span').remove();
	$('#edit-parent-mail-wrapper').children('label').children('span').remove();
	$('#dit-grade-wrapper').children('label').children('span').remove();
	$('#edit-learning-disablity-wrapper').children('label').children('span').remove();
	
	if($("#edit-roles option:selected").text() == 'teacher' || $("#edit-roles option:selected").text() == 'site administrator'){
		$('#edit-teacher-wrapper').hide();
		$('#edit-parent-fname-wrapper').hide();
		$('#edit-parent-lname-wrapper').hide();
		$('#edit-parent-mail-wrapper').hide();
		$('#edit-reason-wrapper').hide();
		$('#edit-grade-wrapper').hide();
		$('#edit-learning-disablity-wrapper').hide();
	}
	else{
		$('#edit-teacher-wrapper').show();
		$('#edit-teacher-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-parent-fname-wrapper').show();
		$('#edit-parent-fname-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-parent-lname-wrapper').show();
		$('#edit-parent-lname-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-parent-mail-wrapper').show();
		$('#edit-parent-mail-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-reason-wrapper').show();
		
		$('#edit-grade-wrapper').show();
		$('#edit-grade-wrappe').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-learning-disablity-wrapper').show();
		$('#edit-learning-disablity-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
	}
}