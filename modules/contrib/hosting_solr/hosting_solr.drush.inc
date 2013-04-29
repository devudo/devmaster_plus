<?php

/**
 * Implements hook_hosting_ENTITYTYPE_context_options() for sites.
 *
 * $task->context_options get passed to provision_solr as drush options,
 * BUT ONLY if you setProperty in subscribe_site!
 */
function hosting_solr_hosting_site_context_options(&$task) {
  if (isset($task->ref->solr_server)) {
    $task->context_options['solr_server'] = hosting_context_name($task->ref->solr_server);
    $task->context_options['solr_config_path'] = $task->ref->solr_config_path;
    $task->context_options['solr_war_path'] = $task->ref->solr_war_path;
  }
}

/**
 * Implements hook_hosting_ENTITYTYPE_context_options() for sites.
 *
 * $task->context_options get passed to provision_solr as drush options,
 * BUT ONLY if you setProperty in subscribe_site!
 */
function hosting_solr_hosting_server_context_options(&$task) {
  if (isset($task->ref->solr_war_path)) {
    $task->context_options['solr_war_path'] = $task->ref->solr_war_path;
  }
}

/**
 * Implementation of hook_drush_context_import().
 */
function hosting_solr_drush_context_import($context, &$node) {
  if ($context->type == 'site') {
    if (isset($context->solr_server)) {
      $node->solr_server = $context->solr_server;
      $node->solr_config_path = $context->solr_config_path;
    }
  }
  if ($context->type == 'server') {
    if (isset($context->solr_war_path)) {
      $node->solr_war_path = $context->solr_war_path;
    }
  }
}
