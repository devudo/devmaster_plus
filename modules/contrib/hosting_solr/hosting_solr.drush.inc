<?php

function hosting_solr_hosting_site_context_options(&$task) {
  if (isset($task->ref->solr_server)) {
    $task->context_options['solr_server'] = hosting_context_name($task->ref->solr_server);
    $task->context_options['solr_config_path'] = $task->ref->solr_config_path;
  }
}

/**
 * Implementation of hook_drush_context_import().
 */
function hosting_solr_drush_context_import($context, &$node) {
  if ($context->type == 'site') {
    // if we clone a site which used solr, we would like to continue using it.
    // TODO: potentially the new server has no solr service..whats then?
    if (isset($context->solr_server)) {
      $node->solr_server = $context->solr_server;
      $node->solr_config_path = $context->solr_config_path;
    }
  }
}
