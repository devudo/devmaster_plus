<?php

/**
 * @file
 *   Expose the solr feature to hostmaster.
 */

/**
 * Implementation of hook_hosting_feature().
 * 
 * Register the solr hosting feature with Aegir, initially this feature will
 * be disabled.
 */
function hosting_solr_hosting_feature() {
  $features['solr'] = array(
    'title' => t('Solr Hosting'),
    'description' => t('Give sites an Apache Solr instance.'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'hosting_solr',
    'group' => 'experimental'
  );
  return $features;
}
