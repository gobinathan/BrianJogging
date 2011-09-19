$(document).ready(function() {
	toggle_parent_fields();
  $('#edit-roles').change(function(){
		toggle_parent_fields();
	});
});

function toggle_parent_fields(){
	if($("#edit-roles option:selected").text() == 'teacher' || $("#edit-roles option:selected").text() == 'site administrator'){
		$('#edit-teacher-wrapper').hide();
		$('#edit-parent-fnmae-wrapper').hide();
		$('#edit-parent-lname-wrapper').hide();
		$('#edit-parent-mail-wrapper').hide();
		$('#edit-reason-wrapper').hide();
		$('#edit-grade-wrapper').hide();
		$('#edit-learning-disablity-wrapper').hide();
	}
	else{
		$('#edit-teacher-wrapper').show();
		$('#edit-parent-fnmae-wrapper').show();
		$('#edit-parent-lname-wrapper').show();
		$('#edit-parent-mail-wrapper').show();
		$('#edit-reason-wrapper').show();
		$('#edit-grade-wrapper').show();
		$('#edit-learning-disablity-wrapper').show();
	}
}