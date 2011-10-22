<?php
/**
 * @file page.tpl.php
 *
 * Theme implementation to display a single Drupal page.
 */
 
// Catch AJAX requests from the App Builder module
if ($_GET["format"] == "ajax") {
  include ('ajax.tpl.php');
  return;
}
?>
<!DOCTYPE html>
<html>
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $body_classes; ?>">
  <div id="header">
       <div class="head"><a href="/"><h1 class="title">Brain Jogging</h1></a></div>
    <?php if($title): ?><h1 class="title" style="font-size:15px;"><?php print $title; ?></h1><?php endif; ?>
      <!--<div id="breadcrumb"><?php //print $breadcrumb; ?></div>-->

    <?php if ($tabs_primary): ?>
      <div id="primary-tabs" class="tabs tabs-primary"><ul class="primary"><?php print $tabs_primary; ?></ul><div class="clear-block"></div></div>
    <?php endif; ?>
  </div>
  
  <?php if ($tabs_secondary): ?>
    <div id="secondary-tabs" class="tabs tabs-secondary"><ul class="secondary"><?php print $tabs_secondary; ?></ul><div class="clear-block"></div></div>
  <?php endif; ?>
    
  <div id="wrapper">
    <div id="wrapper-inner">
      <div id="region-main" class="region">
        <div class="region-inner">
          <?php print $messages; ?>
          <?php if($help): ?>
            <div id="help">
              <?php print $help; ?>
            </div>
          <?php endif; ?>
          <div id="main-content">
            <div class="content">
              <?php print $content; ?>
            </div>
          </div>
        </div>  
      </div> 
      <?php if($right) { ?>
        <div id="region-right" class="region">
          <div class="region-inner">
            <?php echo $right; ?>
          </div>
        </div>
      <?php } ?>
    </div>
  </div>
  <?php print $closure; ?>
</body>
</html>