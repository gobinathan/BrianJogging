<?php 
/**
 * @file template.php
 */

/**
 * Implementation of hook_preprocess_page()
 */
function velo_preprocess_page(&$vars){

  // Add separate tabs for local tasks
  $vars['tabs_primary'] = menu_primary_local_tasks();
  $vars['tabs_secondary'] = menu_secondary_local_tasks();

  // Classes for body element. Allows advanced theming based on context
  // (home page, node of certain type, etc.)
  $classes = explode(' ', $vars['body_classes']);

  if (!$vars['is_front']) {
    // Add unique class for each page.
    $path = drupal_get_path_alias($_GET['q']);
    $classes[] = drupal_html_class('page-' . $path);
    // Add unique class for each website section.
    list($section, ) = explode('/', $path, 2);
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        $section = 'node-add';
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        $section = 'node-' . arg(2);
      }
    }
    $classes[] = drupal_html_class('section-' . $section);
  }

  // Set a class for the sidebar
  if ($vars['right']) {
    $classes[] = 'right-sidebar';
  } else {
    $classes[] = 'no-sidebar';
  }

  $vars['body_classes_array'] = $classes;
  $vars['body_classes'] = implode(' ', $classes); // Concatenate with spaces.
}

/**
 * Implementation of theme_fieldset().
 */
function velo_fieldset($element) {
  $fieldset_classes = array();
  
  !empty($element['#attributes']['class']) ? $fieldset_classes = explode(' ', $element['#attributes']['class']) : $fieldset_classes[] = 'no-attributes';
    
  // build classes for collapsibiles
  if (!empty($element['#collapsible'])) {
    drupal_add_js('misc/collapse.js');
    $fieldset_classes[] = 'collapsible';
    if (!empty($element['#collapsed'])) {
      $fieldset_classes[] = 'collapsed';
    }
  }
  
  // set classes only if they exists
  if(!empty($fieldset_classes)) {
    $element['#attributes']['class'] = implode(' ', $fieldset_classes);
  } else {
    unset($element['#attributes']['class']);
  }

  // set an ID only if one exists
  if(!empty($element['#id'])) {
    $element['#attributes']['id'] = $element['#id'];
  }
  
  // run it all through drupal_attributes
  !empty($element['#attributes']) ? $attributes = drupal_attributes($element['#attributes']) : $attributes = '';

  // build other fieldset components
  $description = !empty($element['#description']) ? "<div class='description'>{$element['#description']}</div>" : '';
  $children = !empty($element['#children']) ? $element['#children'] : '';
  $value = !empty($element['#value']) ? $element['#value'] : '';
  $content = $description . $children . $value;

  // render the fieldset
  $output  = '<div class="fieldset">';
  $output .= '<fieldset' . $attributes . '>';
  if($element['#title']) { $output .= '<legend><span class="title">' . $element['#title'] . '</span></legend>'; }
  $output .= '<div class="fieldset-content">' . $content . '</div>';
  $output .= '</fieldset></div>';
  
  return $output;
}

/**
 * Implements theme_node_add_list()
 *
 * Themes the page for adding content
 */
function velo_node_add_list($content) {
  $output = '';

  if ($content) {
    $output = '<div class="node-type-list">';
    foreach ($content as $item) {
      $output .= '<div class="node-type-row clearfix">';
      $output .= '<div class="node-type-image"><a href="' . $item['href'] . '"></a></div>';
      $output .= '<div class="node-type-about">';
      $output .= '<div class="name">' . l($item['title'] . ' &raquo;', $item['href'], $item['localized_options'])  . '</div>';
      $output .= '<div class="description">' . filter_xss_admin($item['description']) . '</p></div>';
      $output .= '</div></div>';
    }
    $output .= '</div>';
  }
  return $output;
}

/**
 * Override the vocabulary listing to add better CSS classes
 */
function velo_taxonomy_overview_vocabularies($form) {
  $rows = array();
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['name'])) {
      $vocabulary = &$form[$key];

      $row = array();
      $row[] = array('data' => ''); //extra td to make table-drag work better
      $row[] = array('data' => drupal_render($vocabulary['name']), 'class' => 'name');
      $row[] = array('data' => drupal_render($vocabulary['types']), 'class' => 'types');
      if (isset($vocabulary['weight'])) {
        $vocabulary['weight']['#attributes']['class'] = 'vocabulary-weight';
        $row[] = drupal_render($vocabulary['weight']);
      }
      $row[] = array('data' => drupal_render($vocabulary['edit']), 'class' => 'operations edit');
      $row[] = array('data' => drupal_render($vocabulary['list']), 'class' => 'operations list');
      $row[] = array('data' => drupal_render($vocabulary['add']), 'class' => 'operations add');
      $rows[] = array(
        'data' => $row,
        'class' => 'draggable',
      );
    }
  }
  if (empty($rows)) {
    $rows[] = array(array(
        'data' => t('No vocabularies available.'),
        'colspan' => '5',
      ));
  }

  $header = array(array('data' => t('Name'), 'colspan' => '2'), t('Type'));
  if (isset($form['submit'])) {
    $header[] = t('Weight');
    drupal_add_tabledrag('taxonomy', 'order', 'sibling', 'vocabulary-weight');
  }
  $header[] = array(
    'data' => t('Operations'),
    'colspan' => '3',
  );
  return theme('table', $header, $rows, array('id' => 'taxonomy')) . drupal_render($form);
}

/**
 * Theme function for managing options on admin/content/node, admin/user/user.
 */
function velo_admin_manage_options($form) {
  $output = "<div class='clear-block admin-options'>";
  $output .= "<label>{$form['#title']}</label>";
  foreach (element_children($form) as $id) {
    $output .= drupal_render($form[$id]);
  }
  $output .= "</div>";
  return $output;
}

/**
*  Implementation on theme_button()
*/
function velo_button($element) {
  if (isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'] .' '. $element['#attributes']['class'];
  }
  else {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'];
  }

  // Wrap non-hidden input elements with span tags for button graphics
  if (
    velo_stristr('style', $element['#attributes'], 'display: none;') || 
    velo_stristr('class', $element['#attributes'], 'fivestar-submit')  || 
    (array_key_exists('#upload_validators', $element) && (is_array($element['#upload_validators'])))
  ) {
    return '<input type="submit" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ')  .'id="'. $element['#id'].'" value="'. check_plain($element['#value']) .'" '. drupal_attributes($element['#attributes']) ." />\n";
  }
  else {
    return '<span class="button-wrapper"><input type="submit" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ')  .'id="'. $element['#id'].'" value="'. check_plain($element['#value']) .'" '. drupal_attributes($element['#attributes']) ." /></span>\n";
  } 
}

function velo_breadcrumb($breadcrumb) {
   if (!empty($breadcrumb)) {
     return '<div class="breadcrumb">'. implode(' <span class="bc-separator">&gt;</span> ', $breadcrumb) .'</div>';
   }
}

/**
 * E_NOTICE safe version of stristr()
 */
function velo_stristr($hay, $stack, $needle, $before_needle = FALSE){
  if(array_key_exists($hay, $stack) && !is_null($stack[$hay])){
    return stristr($stack[$hay], $needle);
  }
  else {
    return FALSE;
  }
}

/**
 * Extra drupal 7 html selector functions
 */

if (!function_exists('drupal_html_class')) {
  /**
   * Prepare a string for use as a valid class name.
   *
   * Do not pass one string containing multiple classes as they will be
   * incorrectly concatenated with dashes, i.e. "one two" will become "one-two".
   *
   * @param $class
   *   The class name to clean.
   * @return
   *   The cleaned class name.
   */
  function drupal_html_class($class) {
    // By default, we filter using Drupal's coding standards.
    $class = strtr(drupal_strtolower($class), array(' ' => '-', '_' => '-', '/' => '-', '[' => '-', ']' => ''));

    // http://www.w3.org/TR/CSS21/syndata.html#characters shows the syntax for valid
    // CSS identifiers (including element names, classes, and IDs in selectors.)
    //
    // Valid characters in a CSS identifier are:
    // - the hyphen (U+002D)
    // - a-z (U+0030 - U+0039)
    // - A-Z (U+0041 - U+005A)
    // - the underscore (U+005F)
    // - 0-9 (U+0061 - U+007A)
    // - ISO 10646 characters U+00A1 and higher
    // We strip out any character not in the above list.
    $class = preg_replace('/[^\x{002D}\x{0030}-\x{0039}\x{0041}-\x{005A}\x{005F}\x{0061}-\x{007A}\x{00A1}-\x{FFFF}]/u', '', $class);

    return $class;
  }
} /* End of drupal_html_class conditional definition. */

if (!function_exists('drupal_html_id')) {
  /**
   * Prepare a string for use as a valid HTML ID and guarantee uniqueness.
   *
   * @param $id
   *   The ID to clean.
   * @return
   *   The cleaned ID.
   */
  function drupal_html_id($id) {
    $id = strtr(drupal_strtolower($id), array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));

    // As defined in http://www.w3.org/TR/html4/types.html#type-name, HTML IDs can
    // only contain letters, digits ([0-9]), hyphens ("-"), underscores ("_"),
    // colons (":"), and periods ("."). We strip out any character not in that
    // list. Note that the CSS spec doesn't allow colons or periods in identifiers
    // (http://www.w3.org/TR/CSS21/syndata.html#characters), so we strip those two
    // characters as well.
    $id = preg_replace('/[^A-Za-z0-9\-_]/', '', $id);

    return $id;
  }
} /* End of drupal_html_id conditional definition. */