<?php
/**
 * @file hosting_filemanager.editor.inc
 */

/**
 * Load the selected files in a viewer based on extenstion type
 *
 * @todo - theme function
 *       - add editing functionality
 */
function hosting_filemanager_viewer($file, $node) {
  $path = drupal_get_path('module', 'hosting_filemanager');
  $text_formats = array('txt', 'css', 'php', 'module', 'install', 'inc', 'js', 'info');
  $image_formats = array('png', 'jpg', 'gif', 'jpeg', 'ico');
  $video_formats = array('mp4', 'flv');
  $compress_formats = array('gz', 'zip');

  if (($root = hosting_filemanager_root($node)) === FALSE) {
    return "";
  }

  $dir = $root . '/' . $file;
  $ext = _hosting_filemanager_get_extension($dir);

  $output = '<div class="file-viewer"><div class="title">File format: ' . $ext . '</div>';

  $link = url('hosting_filemanager/'. $node->nid .'/file', array('absolute' => TRUE, 'query' => 'file=' . $file));

  if (in_array(strtolower($ext), $text_formats)) {
    drupal_add_css($path . '/hosting_filemanager.css');
    // TODO: error checking
    if (($f = fopen($dir, 'r')) !== FALSE) {
      $contents = fread($f,filesize($dir));
      fclose($f);

      $form_id = form_clean_id('code');

      if (hosting_filemanager_codemirror_library()) {
        $path = drupal_get_path('module', 'hosting_filemanager');
        drupal_add_js($path . '/hosting_filemanager.js');
        hosting_filemanager_include_formats(array('php', 'xml', 'javascript', 'css', 'clike'));

        $readonly = TRUE;
        if (!$readonly) {
          // @todo - provide ability to save file.
          // $output .= '<div class="action-links"><input type="button" value="Save"></div>';
        }

        drupal_add_js('
          $(document).ready(function(){
            var editor = CodeMirror.fromTextArea(document.getElementById("'. $form_id .'"), {
              lineNumbers: true,
              matchBrackets: true,
              mode: "application/x-httpd-php",
              indentUnit: 2,
              indentWithTabs: false,
              enterMode: "keep",
              tabMode: "shift",
              readOnly: '. ($readonly ? 'true' : 'false') .'
            });
          });
        ', 'inline');
      }
      $output .= '<div class="content"><textarea id="'. $form_id . '" class="code">'. $contents .'</textarea></div>';
    }
  }
  elseif (in_array(strtolower($ext), $image_formats)) {
    // @todo - replace with a theme function, maybe using imagecache to create thumbnail of large files.
    $output .= '<img src="' . $link .'"/>';
  }
  elseif (in_array(strtolower($ext), $video_formats)) {
    // @todo: A video file could be played in a embeded player.
    //drupal_add_js($path . '/libraries/flowplayer/example/flowplayer-3.2.6.min.js');
    //$output .= l('', $link,
    //  array('attributes' => array('style' => 'display:block;width:425px;height:300px;', 'id' => 'player')));
    //drupal_add_js('
    //  $(document).ready(function(){
    //    flowplayer("player", "' . $path .'/libraries/flowplayer/flowplayer-3.2.7.swf");
    //  });', 'inline');
    $output .= l('Download', $link);
  }
  elseif (in_array(strtolower($ext), $compress_formats)) {
    // @todo: provide a option to uncompress the file
    //$output .= "<input type='submit' value='Uncompress'>";
    $output .= l('Download', $link);
  }
  else {
    $output .= l('Download', $link);
  }
  $output .= "</div>";
  return $output;
}

/**
 *
 */
function hosting_filemanager_include_formats($formats) {
  $path = hosting_filemanager_codemirror_library();
  foreach ($formats as $format) {
    drupal_add_js($path . '/mode/' . $format . '/' . $format . '.js');
  }
}

/**
 * Load CodeMirror files from libraries path.
 */
function hosting_filemanager_codemirror_library() {
  static $library_path = null;

  if (!isset($library_path)) {
    $library_path = libraries_get_path('CodeMirror');

    if (!file_exists('./'. $library_path .'/lib/codemirror.js') ||
        !file_exists('./'. $library_path .'/lib/codemirror.js')) {
      return FALSE;
    }

    drupal_add_css($library_path . '/lib/codemirror.css');
    drupal_add_js($library_path . '/lib/codemirror.js');
  }
  return $library_path;
}

