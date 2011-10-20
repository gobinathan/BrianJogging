<?php
/**
 * @file ajax.tpl.php
 */
?>
<!DOCTYPE html>
<html>
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="modal-window">
  <div id="wrapper">
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

  </div>
</body>
</html>