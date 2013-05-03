<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function devudo_users_user_default_permissions() {
  $permissions = array();

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: access disabled sites
  $permissions['access disabled sites'] = array(
    'name' => 'access disabled sites',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
    ),
  );

  // Exported permission: access filemanager
  $permissions['access filemanager'] = array(
    'name' => 'access filemanager',
    'roles' => array(),
  );

  // Exported permission: access hosting drush aliases
  $permissions['access hosting drush aliases'] = array(
    'name' => 'access hosting drush aliases',
    'roles' => array(),
  );

  // Exported permission: access hosting logs
  $permissions['access hosting logs'] = array(
    'name' => 'access hosting logs',
    'roles' => array(),
  );

  // Exported permission: access hosting wizard
  $permissions['access hosting wizard'] = array(
    'name' => 'access hosting wizard',
    'roles' => array(),
  );

  // Exported permission: access task logs
  $permissions['access task logs'] = array(
    'name' => 'access task logs',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: administer clients
  $permissions['administer clients'] = array(
    'name' => 'administer clients',
    'roles' => array(),
  );

  // Exported permission: administer hosting
  $permissions['administer hosting'] = array(
    'name' => 'administer hosting',
    'roles' => array(),
  );

  // Exported permission: administer hosting features
  $permissions['administer hosting features'] = array(
    'name' => 'administer hosting features',
    'roles' => array(),
  );

  // Exported permission: administer hosting queues
  $permissions['administer hosting queues'] = array(
    'name' => 'administer hosting queues',
    'roles' => array(),
  );

  // Exported permission: administer hosting settings
  $permissions['administer hosting settings'] = array(
    'name' => 'administer hosting settings',
    'roles' => array(),
  );

  // Exported permission: administer projects
  $permissions['administer projects'] = array(
    'name' => 'administer projects',
    'roles' => array(),
  );

  // Exported permission: administer sites
  $permissions['administer sites'] = array(
    'name' => 'administer sites',
    'roles' => array(),
  );

  // Exported permission: administer tasks
  $permissions['administer tasks'] = array(
    'name' => 'administer tasks',
    'roles' => array(),
  );

  // Exported permission: cancel own tasks
  $permissions['cancel own tasks'] = array(
    'name' => 'cancel own tasks',
    'roles' => array(),
  );

  // Exported permission: configure devshop pull
  $permissions['configure devshop pull'] = array(
    'name' => 'configure devshop pull',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create backup task
  $permissions['create backup task'] = array(
    'name' => 'create backup task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create backup_delete task
  $permissions['create backup_delete task'] = array(
    'name' => 'create backup_delete task',
    'roles' => array(),
  );

  // Exported permission: create client
  $permissions['create client'] = array(
    'name' => 'create client',
    'roles' => array(),
  );

  // Exported permission: create clone task
  $permissions['create clone task'] = array(
    'name' => 'create clone task',
    'roles' => array(),
  );

  // Exported permission: create delete task
  $permissions['create delete task'] = array(
    'name' => 'create delete task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create devshop-commit task
  $permissions['create devshop-commit task'] = array(
    'name' => 'create devshop-commit task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create devshop-create task
  $permissions['create devshop-create task'] = array(
    'name' => 'create devshop-create task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create devshop-delete task
  $permissions['create devshop-delete task'] = array(
    'name' => 'create devshop-delete task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create devshop-pull task
  $permissions['create devshop-pull task'] = array(
    'name' => 'create devshop-pull task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create devshop-sync task
  $permissions['create devshop-sync task'] = array(
    'name' => 'create devshop-sync task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create disable task
  $permissions['create disable task'] = array(
    'name' => 'create disable task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create enable task
  $permissions['create enable task'] = array(
    'name' => 'create enable task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create lock task
  $permissions['create lock task'] = array(
    'name' => 'create lock task',
    'roles' => array(),
  );

  // Exported permission: create login_reset task
  $permissions['create login_reset task'] = array(
    'name' => 'create login_reset task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create migrate task
  $permissions['create migrate task'] = array(
    'name' => 'create migrate task',
    'roles' => array(),
  );

  // Exported permission: create package
  $permissions['create package'] = array(
    'name' => 'create package',
    'roles' => array(),
  );

  // Exported permission: create platform
  $permissions['create platform'] = array(
    'name' => 'create platform',
    'roles' => array(),
  );

  // Exported permission: create project
  $permissions['create project'] = array(
    'name' => 'create project',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create restore task
  $permissions['create restore task'] = array(
    'name' => 'create restore task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: create server
  $permissions['create server'] = array(
    'name' => 'create server',
    'roles' => array(),
  );

  // Exported permission: create site
  $permissions['create site'] = array(
    'name' => 'create site',
    'roles' => array(),
  );

  // Exported permission: create unlock task
  $permissions['create unlock task'] = array(
    'name' => 'create unlock task',
    'roles' => array(),
  );

  // Exported permission: create verify task
  $permissions['create verify task'] = array(
    'name' => 'create verify task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete own client
  $permissions['delete own client'] = array(
    'name' => 'delete own client',
    'roles' => array(),
  );

  // Exported permission: delete package
  $permissions['delete package'] = array(
    'name' => 'delete package',
    'roles' => array(),
  );

  // Exported permission: delete platform
  $permissions['delete platform'] = array(
    'name' => 'delete platform',
    'roles' => array(),
  );

  // Exported permission: delete projects
  $permissions['delete projects'] = array(
    'name' => 'delete projects',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: delete server
  $permissions['delete server'] = array(
    'name' => 'delete server',
    'roles' => array(),
  );

  // Exported permission: delete site
  $permissions['delete site'] = array(
    'name' => 'delete site',
    'roles' => array(),
  );

  // Exported permission: edit client uname
  $permissions['edit client uname'] = array(
    'name' => 'edit client uname',
    'roles' => array(),
  );

  // Exported permission: edit client users
  $permissions['edit client users'] = array(
    'name' => 'edit client users',
    'roles' => array(),
  );

  // Exported permission: edit own client
  $permissions['edit own client'] = array(
    'name' => 'edit own client',
    'roles' => array(),
  );

  // Exported permission: edit package
  $permissions['edit package'] = array(
    'name' => 'edit package',
    'roles' => array(),
  );

  // Exported permission: edit platform
  $permissions['edit platform'] = array(
    'name' => 'edit platform',
    'roles' => array(),
  );

  // Exported permission: edit project
  $permissions['edit project'] = array(
    'name' => 'edit project',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: edit server
  $permissions['edit server'] = array(
    'name' => 'edit server',
    'roles' => array(),
  );

  // Exported permission: edit site
  $permissions['edit site'] = array(
    'name' => 'edit site',
    'roles' => array(),
  );

  // Exported permission: retry failed tasks
  $permissions['retry failed tasks'] = array(
    'name' => 'retry failed tasks',
    'roles' => array(),
  );

  // Exported permission: view client
  $permissions['view client'] = array(
    'name' => 'view client',
    'roles' => array(),
  );

  // Exported permission: view git commit logs
  $permissions['view git commit logs'] = array(
    'name' => 'view git commit logs',
    'roles' => array(),
  );

  // Exported permission: view locked platforms
  $permissions['view locked platforms'] = array(
    'name' => 'view locked platforms',
    'roles' => array(),
  );

  // Exported permission: view own tasks
  $permissions['view own tasks'] = array(
    'name' => 'view own tasks',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view package
  $permissions['view package'] = array(
    'name' => 'view package',
    'roles' => array(),
  );

  // Exported permission: view platform
  $permissions['view platform'] = array(
    'name' => 'view platform',
    'roles' => array(),
  );

  // Exported permission: view project
  $permissions['view project'] = array(
    'name' => 'view project',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view projects
  $permissions['view projects'] = array(
    'name' => 'view projects',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view server
  $permissions['view server'] = array(
    'name' => 'view server',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view site
  $permissions['view site'] = array(
    'name' => 'view site',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  // Exported permission: view task
  $permissions['view task'] = array(
    'name' => 'view task',
    'roles' => array(
      '0' => 'authenticated user',
    ),
  );

  return $permissions;
}
