<?php

/**
 * The base service type class , registered with hook_hosting_service_type.
 */
class hostingService_solr extends hostingService {
 /**
  * the value stored in the service column of hosting_service table.
  */
  public $service = 'solr';
}

/**
 * Public instance of hostingService_solr
 */
class hostingService_solr_public extends hostingService_solr {
  protected $has_port = TRUE;

  function default_port() {
    return 8080;
  }

  function update() {
    parent::update();
  }
  
  public function context_options($task_type, $ref_type, &$task) {
    parent::context_options($task_type, $ref_type, $task);
  }
}

/**
 * An implementation of the solr service type, registered with hook_hosting_service.
 */

class hostingService_solr_tomcat extends hostingService_solr_public {
 /**
  * the value stored in the type column of the hosting_service table.
  */
  public $type = 'tomcat';

 /**
  * this service needs to be restarted with a shell command.
  */
  protected $has_restart_cmd = TRUE;
  
  function default_restart_cmd() {
    $command = '/etc/init.d/tomcat7'; // A proper default for most of the world
    //$options[] = $command;
    //foreach ($options as $test) {
    //  if (is_executable($test)) {
    //    $command = $test;
    //    break;
    //  }
    //}
    return "sudo $command restart";
  }
}

