<?php
/**
 *
 */

/**
 * Profile a passthru to get a file relative to the node.
 */
function hosting_filemanager_file($node) {
  if ($node->type == 'site') {
    $platform = node_load($node->platform);
    $root = $platform->publish_path . '/sites/' . $node->title;
  }
  elseif ($noe->type == 'platform') {
    $root = $node->publish_path;
  }
  else {
    return "Error";
  }
  $file = $root . $_GET['file']; // todo: clean

  $ext = _hosting_filemanager_get_extension($dir);

  // open the file in a binary mode
  $fp = fopen($file, 'rb');

  // send the right headers
  //header("Content-Type: image/png");
  header("Content-Length: " . filesize($file));
  header('Content-Disposition: attachment; filename="' . basename($file) . '"');

  fpassthru($fp);
  fclose($fp);
  exit;
}

/**
 * Human friendly file size.
 */
function _hosting_filemanager_format_file_size( $size, $display_bytes=false ) {
  if( $size < 1024 ) {
    $filesize = $size . ' bytes';
  }
  elseif( $size >= 1024 && $size < 1048576 ) {
    $filesize = round( $size/1024, 2 ) . ' KB';
  }
  elseif( $size >= 1048576 ) {
    $filesize = round( $size/1048576, 2 ) . ' MB';
  }

  if( $size >= 1024 && $display_bytes ) {
    $filesize = $filesize . ' (' . $size . ' bytes)';
  }
  return $filesize;
}

/**
 * Get the permission of file and convert to a linux style e.g. rw-rw-rw-
 */
function _hosting_filemanager_perm($path) {
 $perms = fileperms($path);

  if (($perms & 0xC000) == 0xC000) {
    // Socket
    $info = 's';
  }
  elseif (($perms & 0xA000) == 0xA000) {
    // Symbolic Link
    $info = 'l';
  }
  elseif (($perms & 0x8000) == 0x8000) {
    // Regular
    $info = '-';
  }
  elseif (($perms & 0x6000) == 0x6000) {
    // Block special
    $info = 'b';
  }
  elseif (($perms & 0x4000) == 0x4000) {
    // Directory
    $info = 'd';
  }
  elseif (($perms & 0x2000) == 0x2000) {
    // Character special
    $info = 'c';
  }
  elseif (($perms & 0x1000) == 0x1000) {
    // FIFO pipe
    $info = 'p';
  }
  else {
    // Unknown
    $info = 'u';
  }

  // Owner
  $info .= (($perms & 0x0100) ? 'r' : '-');
  $info .= (($perms & 0x0080) ? 'w' : '-');
  $info .= (($perms & 0x0040) ?
    (($perms & 0x0800) ? 's' : 'x' ) :
    (($perms & 0x0800) ? 'S' : '-'));

  // Group
  $info .= (($perms & 0x0020) ? 'r' : '-');
  $info .= (($perms & 0x0010) ? 'w' : '-');
  $info .= (($perms & 0x0008) ?
    (($perms & 0x0400) ? 's' : 'x' ) :
    (($perms & 0x0400) ? 'S' : '-'));

  // World
  $info .= (($perms & 0x0004) ? 'r' : '-');
  $info .= (($perms & 0x0002) ? 'w' : '-');
  $info .= (($perms & 0x0001) ?
    (($perms & 0x0200) ? 't' : 'x' ) :
    (($perms & 0x0200) ? 'T' : '-'));

  return $info;
}


/**
 * Get the user:owner of a file.
 */
function _hosting_filemanager_own($filename) {
  $owner = posix_getpwuid(fileowner($filename));
  $group = posix_getgrgid(filegroup($filename));
  return $owner['name'] . ':' . $group['name'];
}
