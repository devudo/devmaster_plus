<?php

define('DRUSH_PERM_GRANT_NO_ROLES', dt('You must specify roles to grant permissions to, using the --roles option.'));
define('DRUSH_PERM_GRANT_NO_PERMS', dt('You must specify permissions to grant, using the --permissions option.'));

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function permissions_api_drush_help($section) {
    switch ($section) {
      case 'drush:perm-grant':
        return dt("Grant permissions to a role.");
      case 'drush:perm-revoke':
        return dt("Revoke permissions from a role.");
      case 'drush:perm-copy':
        return dt("Copy permissions from one role to another.");
      case 'drush:perm-list':
        return dt("List permissions assigned to a role.");
      case 'drush:role-create':
        return dt("Create a role.");
      case 'drush:role-delete':
        return dt("Delete a role.");
    }
}

/**
 * Implementation of hook_drush_command().
 *
 * Provides a definition of supported actions with their callbacks, options,
 * dependencies, and examples of usage.
 * 
 * @return array - An associative array describing your command(s).
 */
function permissions_api_drush_command() {
  $items=array();

  // Define the perm-grant action
  $items['perm-grant'] = array(
    'callback' => 'drush_permissions_api_perm_grant',
    'description' => dt('Grant permissions to a role.'),
    'options' => array(
      'all-roles' => dt('Grant the permissions to all defined roles.'),
      'roles' => dt('Comma-separated list of roles to grant permissions to.'),
      'permissions' => dt('Comma-separated list of permissions to grant to a role or roles.'),
      'modules' => dt('Comma-separated list of modules providing permissions to grant.'),
      'all-modules' => dt('Grant all defined permissions to a role or roles.'),
    ),
    'examples' => array(
      'drush perm-grant --roles="Admin" --modules="node"' => dt('Grant all permissions provided by the Node module to the Admin role.'),
      'drush perm-grant --all-modules --roles-="Admin"' => dt('Grant all permissions to Admin role.'),
      'drush perm-grant --roles="Editor,Copy Editor" --permissions="administer nodes"' => dt('Grant "administer nodes" to Editor and Copy Editor roles.'),
      'drush perm-grant --all-roles --permissions="administer nodes"' => dt('Grant "administer nodes" permission to all roles.'),
    ),
    'drupal dependencies' => array('permissions_api'),
  );

  // Define the perm-revoke action
  $items['perm-revoke'] = array(
    'callback' => 'drush_permissions_api_perm_revoke',
    'description' => dt('Revoke permissions from a role.'),
    'options' => array(
      'all-roles' => dt('Revoke the permissions from all defined roles.'),
      'roles' => dt('Comma-separated list of roles to revoke permissions from.'),
      'permissions' => dt('Comma-separated list of permissions to revoke from a role or roles.'),
      'modules' => dt('Comma-separated list of modules providing permissions to revoke.'),
      'all-modules' => dt('Revoke all defined permissions from a role or roles.'),
      'reset' => dt('Revoke all defined permissions from all roles.  Requires confirmation, use with caution.'),
    ),
    'examples' => array(
      'drush perm-revoke --roles="Admin" --modules="node"' => dt('Revoke all permissions provided by the Node module from the Admin role.'),
      'drush perm-revoke --all-modules --roles-="Admin"' => dt('Revoke all permissions from the Admin role.'),
      'drush perm-revoke --roles="Editor,Copy Editor" --permissions="administer nodes"' => dt('Revoke "administer nodes" from the Editor and Copy Editor roles.'),
      'drush perm-revoke --all-roles --permissions="administer nodes"' => dt('Revoke "administer nodes" permission from all roles.'),
      'drush perm-revoke --reset' => dt('Revoke all permissions from all roles.  Requires confirmation, use with caution.'),
    ),
    'drupal dependencies' => array('permissions_api'),
  );

  // Define the perm-copy action
  $items['perm-copy'] = array(
    'callback' => 'drush_permissions_api_perm_copy',
    'description' => dt('copy permissions from one role to another.'),
    'arguments' => array(
      'source role' => dt('The name of the role you are copying from.'),
      'destination role' => dt('The name of the role you are copying to.'),
    ),
    'examples' => array(
      'drush perm-copy Editor Manager' => dt('Copy permissons from Editor role to Manager role.'),
    ),
    'drupal dependencies' => array('permissions_api'),
  );

  $items['role-create'] = array(
    'callback' => 'drush_permissions_api_role_create',
    'description' => dt('Create a role.'),
    'arguments' => array(
      'role' => dt('The name of the role you are creating.'),
    ),
    'examples' => array(
      'drush role-create Admin' => dt('Create Admin role.'),
    ),
    'drupal dependencies' => array('permissions_api'),
  );

  $items['role-delete'] = array(
    'callback' => 'drush_permissions_api_role_delete',
    'description' => dt('Delete a role.'),
    'arguments' => array(
      'role' => dt('The name of the role you are deleting.'),
    ),
    'examples' => array(
      'drush role-delete Admin' => dt('Delete Admin role.'),
    ),
    'drupal dependencies' => array('permissions_api'),
  );

  $items['perm-list'] = array(
    'callback' => 'drush_permissions_api_perm_list',
    'description' => dt('List permissions for a role.'),
    'arguments' => array(
      'role' => dt('The name of the role you are querying.'),
    ),
    'examples' => array(
      'drush perm-list Admin' => dt('List permissions for Admin role.'),
    ),
    'drupal dependencies' => array('permissions_api'),
  );

  return $items;
}

/**
 * Command callbacks.
 */


/**
 * This function provides functionality for granting permissions to roles via
 * several different mechanisms.
 * 
 * Supported operations are:<ul>
 * <li>grant N permissions to a role(s)</li>
 * <li>grant ALL permissions to a role(s)</li>
 * <li>grant N permissions to ALL roles</li>
 * <li>grant ALL permissions provided by a module to a role(s)</li>
 * <li>grant ALL permissions provided by a module to ALL roles</li>
 * <li>grant ALL permissions a role has to another role(s)</li>
 * </ul>
 */
function drush_permissions_api_perm_grant() {
  
  // Determine if the permissions should be granted to specific roles or to all roles
  $all_roles = false;
  if(! drush_get_option('all-roles')) {
    // Get the specified roles
    $roles = _get_roles_option();
  }
  else {
    $all_roles = true;
  }
  
  /*
   * Determine if permissions provided by specific modules should be granted, 
   * or if all defined permissions should be granted.
   */
  $all_modules = false;
  if(! drush_get_option('all-modules')) {
    if($modules_option = drush_get_option('modules')) {
      $modules = explode(',', $modules_option); 
    } 
    else {
      // Get the specified permissions
      $permissions = _get_permissions_option();
    }
  }
  else {
    $all_modules = true;
  }
  
  // Grant perms by module or by all modules
  if($all_modules) {
    // Grant all defined permissions to a role or roles
    if(! empty($roles)) {
      foreach($roles as $role) {
        if(permissions_grant_all_permissions($role)) {
          drush_print(dt('Granted all permissions to the !role role.', array('!role' => $role)));
        }
        else {
          drush_set_error(WATCHDOG_ERROR, dt('Failed to grant all permissions to the !role role.  Errors have been logged in watchdog.', array('!role' => $role)));
          drush_die();
        }
      }
      return true;
    }
  }
  elseif(!empty($modules)) {
    foreach($modules as $module) {
      if($all_roles) {
        if(permissions_grant_all_permissions_by_module_to_all_roles($module, true)) {
          drush_print(dt('Granted all !module permissions to all roles.', array('!module' => $module)));
        }
        else {
          drush_set_error(WATCHDOG_ERROR, dt('Failed to grant all !module permissions to all roles.  Errors have been logged in watchdog.', array('!module' => $module)));
          drush_die();
        }
      }
      else {
        foreach($roles as $role) {
          if(permissions_grant_all_permissions_by_module($role, $module)) {
            drush_print(dt('Granted all !module permissions to !role.', array('!module' => $module, '!role' => $role)));
          }
          else {
            drush_set_error(WATCHDOG_ERROR, dt('Failed to grant all !module permissions to !role', array('!module' => $module, '!role' => $role)));
            drush_die();
          }
        }
      }
    }
    return true;
  }
  
  // Grant perms to all roles
  if($all_roles) {
    if(!empty($permissions)) {
      if(permissions_grant_permissions_to_all_roles($permissions)) {
        drush_print(dt('Granted permissions to all roles.'));
      }
      else {
        drush_set_error(WATCHDOG_ERROR, dt('Failed to grant permisions to all roles.  Errors have been logged in watchdog.'));
        drush_die();
      }
    }
  }
  elseif(!empty($roles)) {
    if(!empty($permissions)) {
      foreach($roles as $role) {
        if(!permissions_grant_permissions($role, $permissions)) {
          drush_set_error(WATCHDOG_ERROR, dt('Failed to grant permissions to the !role role.  Errors have been logged in watchdog.', array('!role' => $role)));
          drush_die(); 
        }
      }
      drush_print(dt('Granted permissions to the !role role.', array('!role' => $role)));
    }
  }
  
}

/**
 * Provides functionality for revoking permissions from roles.
 * 
 * Supported options are:<ul>
 * <li>revoke N permissions from a role(s)</li>
 * <li>revoke N permissions from a role(s)</li>
 * <li>revoke N permissions from ALL roles</li>
 * <li>revoke ALL permissions provided by a module from a role(s)</li>
 * <li>revoke ALL permissions provided by a module from ALL roles</li>
 * <li>revoke ALL permissions a role has from another role(s)</li>
 * </ul>
 */
function drush_permissions_api_perm_revoke() {
  $reset = false;
  if(drush_get_option('reset')) {
    $reset = true;
  }
  else {
    // Determine if the permissions should be revoked from specific roles or from all roles
    $all_roles = false;
    if(! drush_get_option('all-roles')) {
      // Get the specified roles
      $roles = _get_roles_option();
    }
    else {
      $all_roles = true;
    }
    
    /*
     * Determine if permissions provided by specific modules should be revoked, 
     * or if all defined permissions should be revoked.
     */
    $all_modules = false;
    if(! drush_get_option('all-modules')) {
      if($modules_option = drush_get_option('modules')) {
        $modules = explode(',', $modules_option); 
      } 
      else {
        // Get the specified permissions
        $permissions = _get_permissions_option();
      }
    }
    else {
      $all_modules = true;
    }
  }
  
  // Revoke perms by module or by all modules
  if($all_modules) {
    // Revoke all defined permissions from a role or roles
    if(! empty($roles)) {
      foreach($roles as $role) {
        if(permissions_revoke_all_permissions($role)) {
          drush_print(dt('Revoked all permissions from the !role role.', array('!role' => $role)));
        }
        else {
          drush_set_error(WATCHDOG_ERROR, dt('Failed to revoke all permissions from the !role role.  Errors have been logged in watchdog.', array('!role' => $role)));
          drush_die();
        }
      }
      return true;
    }
    
    // Allow permissions reset using the --all-modules and --all-modules options together
    if($all_modules) {
      if (!drush_confirm(dt('You are about to revoke all permissions from all roles.  Are you sure you want to do this?'))) {
        return drush_user_abort();
      }
      
      if(permissions_reset()) {
        drush_print(dt('All permissions have been reset.'));
        return true;
      }
      else {
        drush_set_error(WATCHDOG_ERROR, dt('Failed to reset all permissions.'));
        drush_die();
      }
    }
    
    drush_set_error(WATCHDOG_ERROR, dt('You must specify roles to revoke permissions from.  Specify roles with the --roles option.'));
    drush_die();
  }
  elseif(!empty($modules)) {
    foreach($modules as $module) {
      if($all_roles) {
        if(permissions_revoke_all_permissions_by_module_from_all_roles($module, true)) {
          drush_print(dt('Revoked all !module permissions from all roles.', array('!module' => $module)));
        }
        else {
          drush_set_error(WATCHDOG_ERROR, dt('Failed to revoke all !module permissions to all roles.  Errors have been logged in watchdog.', array('!module' => $module)));
          drush_die();
        }
      }
      else {
        foreach($roles as $role) {
          if(permissions_revoke_all_permissions_by_module($role, $module)) {
            drush_print(dt('Revoked all !module permissions from !role.', array('!module' => $module, '!role' => $role)));
          }
          else {
            drush_set_error(WATCHDOG_ERROR, dt('Failed to revoke all !module permissions from !role', array('!module' => $module, '!role' => $role)));
            drush_die();
          }
        }
      }
    }
    return true;
  }
  
  // Revoke perms from all roles
  if($all_roles) {
    if(!empty($permissions)) {
      if(permissions_revoke_permissions_from_all_roles($permissions, true)) {
        drush_print(dt('Revoked permissions from all roles.'));
      }
      else {
        drush_set_error(WATCHDOG_ERROR, dt('Failed to revoke permisions from all roles.  Errors have been logged in watchdog.'));
        drush_die();
      }
    }
  }
  elseif(!empty($roles)) {
    if(!empty($permissions)) {
      foreach($roles as $role) {
        if(!permissions_revoke_permissions($role, $permissions)) {
          drush_set_error(WATCHDOG_ERROR, dt('Failed to revoke permissions from the !role role.  Errors have been logged in watchdog.', array('!role' => $role)));
          drush_die(); 
        }
      }
      drush_print(dt('Revoked permissions from the !role role.', array('!role' => $role)));
    }
  }
  
  // Handle permissions reset command
  if($reset) {
    if (!drush_confirm(dt('You are about to revoke all permissions from all roles.  Are you sure you want to do this?'))) {
      return drush_user_abort();
    }
    
    if(permissions_reset()) {
      drush_print(dt('All permissions have been reset.'));
    }
    else {
      drush_set_error(WATCHDOG_ERROR, dt('Failed to reset all permissions.'));
      drush_die();
    }
  }
}

function drush_permissions_api_perm_copy() {
  $args = func_get_args();
  permissions_role_inherit($args[1], $args[0]);
  drush_print(dt('Permissions copied from !from to !to.', array('!from' => $args[0], '!to' => $args[1])));
}

function drush_permissions_api_perm_list() {
  $args = func_get_args();
  foreach($args as $role) {
    $perms = permissions_get_permissions_for_role($role);
    drush_print(dt('Permissions for role !role:', array('!role' => $role)));
    foreach($perms as $perm) {
      drush_print('    '.$perm);
    }
  }
}

function drush_permissions_api_role_create() {
  $args = func_get_args();
  foreach($args as $role) {
    permissions_create_role($role);
    drush_print(dt('Role !role created.', array('!role' => $role)));
  }
}

function drush_permissions_api_role_delete() {
  $args = func_get_args();
  foreach ($args as $role) {
    permissions_delete_role($role);
    drush_print(dt('Role !role deleted.', array('!role' => $role)));
  }
}

/**
 * Internal function to process the roles option specified on the command line
 * and handle any errors.
 * 
 * @return array - Returns an array of strings representing role names
 */
function _get_roles_option() {
  $roles = array();
  if($roles_option = drush_get_option('roles')) {
    $roles = explode(',', $roles_option);
    if(empty($roles)) {
      drush_set_error(WATCHDOG_ERROR, DRUSH_PERM_GRANT_NO_ROLES);
      drush_die();
    }
  }
  else {
    drush_set_error(WATCHDOG_ERROR, DRUSH_PERM_GRANT_NO_ROLES);
    drush_die();
  }
  return $roles;
}

/**
 * Internal function to process the permissions option specified on the command
 * line, and handle any errors.
 * 
 * @return array - Returns an array of strings representing permissions
 */
function _get_permissions_option() {
  $permissions = array();
  if($permissions_option = drush_get_option('permissions')) {
    $permissions = explode(',', $permissions_option);
    if(empty($permissions)) {
      drush_set_error(WATCHDOG_ERROR, DRUSH_PERM_GRANT_NO_PERMS);
      drush_die();
    }
  }
  else {
    drush_set_error(WATCHDOG_ERROR, DRUSH_PERM_GRANT_NO_PERMS);
    drush_die();
  }
  return $permissions;
}