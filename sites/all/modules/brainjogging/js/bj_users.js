$(document).ready(function() {
	toggle_parent_fields();
  $('#edit-roles').change(function(){
		toggle_parent_fields();
	});
});

function toggle_parent_fields(){
	$('#edit-teacher-wrapper').children('label').children('span').remove();
	$('#edit-profile-parent-fname-wrapper').children('label').children('span').remove();
	$('#edit-profile-parent-lname-wrapper').children('label').children('span').remove();
	$('#edit-profile-parent-email-wrapper').children('label').children('span').remove();
	$('#edit-grade-wrapper').children('label').children('span').remove();
	$('#edit-learning-disablity-wrapper').children('label').children('span').remove();
	$('#edit-school-wrapper').children('label').children('span').remove();
	$('#edit-profile-expire-date-wrapper').children('label').children('span').remove();
	
	if($("#edit-roles option:selected").text() == 'teacher' || $("#edit-roles option:selected").text() == 'school administrator'){
		$('#edit-profile-parent-fname-wrapper').hide();
		$('#edit-profile-parent-lname-wrapper').hide();
		$('#edit-profile-parent-email-wrapper').hide();
		$('#edit-profile-expire-date-wrapper').hide();
		//$('#edit-profile-reason-wrapper').parent('fieldset').hide();
		$('#edit-teacher-wrapper').hide();
		$('#edit-profile-reason-wrapper').hide();
		$('#edit-grade-wrapper').hide();
		$('#edit-learning-disablity-wrapper').hide();
		$('#edit-profile-reason-wrapper').parent('fieldset').show();
		$('#edit-school-wrapper').show();
		$('#edit-school-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
	}
	else if($("#edit-roles option:selected").text() == 'site administrator'){
		$('#edit-profile-parent-fname-wrapper').hide();
		$('#edit-profile-parent-lname-wrapper').hide();
		$('#edit-profile-parent-email-wrapper').hide();
		$('#edit-profile-reason-wrapper').parent('.fieldset-content').parent('fieldset').parent('div').hide();
		$('#edit-profile-expire-date-wrapper').hide();
		//$('#edit-school-wrapper').hide();
	}
	else{
		$('#edit-profile-reason-wrapper').parent('fieldset').show();
		$('#edit-school-wrapper').show();
		$('#edit-school-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-teacher-wrapper').show();
		$('#edit-teacher-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-parent-fname-wrapper').show();
		$('#edit-profile-parent-fname-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-parent-lname-wrapper').show();
		$('#edit-profile-parent-lname-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-parent-email-wrapper').show();
		$('#edit-profile-parent-email-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-reason-wrapper').show();
		
		$('#edit-grade-wrapper').show();
		$('#edit-grade-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-learning-disablity-wrapper').show();
		$('#edit-learning-disablity-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
		
		$('#edit-profile-expire-date-wrapper').show();
		$('#edit-profile-expire-date-wrapper').children('label').append('<span title="This field is required." class="form-required">*</span>');
	}
}