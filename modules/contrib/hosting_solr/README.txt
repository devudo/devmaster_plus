Aegir Apache Solr
=================

This module allows Solr servers to be added to Aegir. Once you have a server,
you can give an Aegir Site a Solr database as easily as choosing it's DB Server.

Hosting Solr is the front-end, and Provision Solr is the backend.

Installation
============

You will need Aegir and Provision Solr to use this module.

See http://drupal.org/project/provision_solr for instructions on installing
Provision Solr, Solr and Tomcat.

Once you've got Aegir and Provision Solr and all of it's requirements installed,
download and install this module:

    drush @hostmaster dl hosting_solr
    drush @hostmaster en hosting_solr

Usage
=====
Using Hosting Solr is straightforward once installed and enabled:

1. Visit the Servers page in your Aegir front-end.

2. Click on the server you wish to enable Solr.

3. Click the Edit tab.

4. Under Solr, choose Tomcat. Confirm the Port and Restart command are correct
for your server. If you followed the instructions for Provision Solr exactly the
defaults will work.

5. Hit the Save button.

6. Next, we need to enable Solr for a site. First add the modules ApacheSolr or
Search API + Search API Solr to the Drupal site's platform.

7. Visit the Sites page in your Aegir front-end.

8. Click the Edit tab.

9. Under Solr server choose the server you just configured.

10. Add the Path to solr config files for this site.

11. Hit the Save button

12. Wait for the Verify task to finish, then click the Solr URL provided on the
site's page to confirm Solr was setup properly!

13. In the Drupal site, configure your Solr servers based on the Solr URL. This
part varies depending on whether you are using Search API or Apachesolr.modules.

14. With the server configured, you can now enable Solr on any of the other
sites on your Aegir server by simply Editing the site nodes.

The Solr server's created by Aegir are made available at the following URL:

    http://SERVER_NAME:8080/SITE_NAME

Credits
=======

Hosting & Provision Solr was built by the team at ThinkDrop Consulting.

It was inspired by https://github.com/EugenMayer/aegir_solr_service.