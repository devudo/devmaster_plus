<?php
/**
 * Implements hook_hosting_drush_aliases_name()
 *
 * Simply return the desired alias name.  The last module
 * to implement this hook wins.  Alter your module's weight
 * if needed.
 */
function hook_hosting_drush_aliases_name($node) {
  return $node->title;
}