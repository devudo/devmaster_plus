<?php

/**
 * Implementation of hook_user_default_roles().
 */
function devudo_users_user_default_roles() {
  $roles = array();

  // Exported role: administrator
  $roles['administrator'] = array(
    'name' => 'administrator',
  );

  // Exported role: project admin
  $roles['project admin'] = array(
    'name' => 'project admin',
  );

  return $roles;
}
