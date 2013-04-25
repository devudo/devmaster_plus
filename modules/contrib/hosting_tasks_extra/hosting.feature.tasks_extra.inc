<?php
/**
 * @file
 *   Expose the extra tasks feature to hostmaster.
 */

/**
 * Implementation of hook_hosting_feature().
 */
function hosting_tasks_extra_hosting_feature() {
  $features['tasks_extra'] = array(
    'title' => t('Extra tasks'),
    'description' => t('Additional tasks that can run on sites.'),
    'status' => HOSTING_FEATURE_ENABLED,
    'module' => 'hosting_tasks_extra',
    );
  return $features;
}

