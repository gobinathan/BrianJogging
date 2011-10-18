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
		$('#edit-profile-parent-fname-wrapper').hide();
		$('#edit-profile-parent-lname-wrapper').hide();
		$('#edit-profile-parent-email-wrapper').hide();
		$('#edit-profile-reason-wrapper').parent('fieldset').hide();
		//$('#edit-teacher-wrapper').hide();
		//$('#edit-profile-reason-wrapper').hide();
		//$('#edit-grade-wrapper').hide();
		//$('#edit-learning-disablity-wrapper').hide();
	}
	else{
		//$('#edit-teacher-wrapper').show();
		$('#edit-teacher-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-parent-fname-wrapper').show();
		$('#edit-profile-parent-fname-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-parent-lname-wrapper').show();
		$('#edit-profile-parent-lname-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-parent-email-wrapper').show();
		$('#edit-profile-parent-email-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		//$('#edit-profile-reason-wrapper').show();
		
		//$('#edit-grade-wrapper').show();
		$('#edit-grade-wrappe').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		//$('#edit-learning-disablity-wrapper').show();
		$('#edit-learning-disablity-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
	}
}