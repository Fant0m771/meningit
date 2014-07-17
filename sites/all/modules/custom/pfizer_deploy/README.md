Pfizer Deploy
=============

Pfizer Deploy Core Feature

This feature is the early version of everything you will need to use Deploy along with WF Tools.
This is in an experimental state, and does require some additional setup to get working.  Please see notes below.
This feature depends on very specific versions of several modules:

* ctools
* deploy
* deploy_auto_plan
* deploy_ui
* entity
* entity_dependency
* libraries
* rest_server
* services
* uuid
* uuid_services

These modules are all included via the pfizer_deploy.make file.
Please ensure that you are using these exact versions or you may encounter unexpected results.

This also creates:

* default deploy endpoint (note presently you must change the destination user/pass and url)
* example deployment plan

In order to get this working, you will need 2 identical versions of a site in 2 separate environments.  The latest version also removes the services endpoint definition.

The services endpoint is now going to be defined in a site specific base module that will be generated for all new sites.  The primary reason for this is so that developers can add services resources to the endpoint specific to the site.  Tentative location for the skeleton for this site specific module is located here: https://github.com/pfizer/buildscripts/tree/master/drupal_modules/pfizer_site_module.

IMPORTANT
=========

Even though the deployment endpoints and plans have been created in the feature, the credentials are actually meant to be put in a $conf array.
To that end, for testing purposes please use the form at admin/config/pfizer/pfizer_deploy to edit the credentials.
Also there is a global debug mode that will turn on debugging for the endpoint, plan, services endpoint and custom functions.
Again please set this in the Pfizer Deploy configuration section and not on the individual components.

This feature currently works with these additional contrib modules:

* bean
* entityreference
* og (organic groups)
* entityform
* field_collection (enable the optional pfizer_deploy_fc submodule)
* webform & webform validation (enable the optional pfizer_deploy_webform submodule)
* nodehierarchy (enable the optional pfizer_deploy_nodehierarchy submodule)

Support is currently being worked on/in an indeterminate state for:

* panelizer
* profile2
* etc...

Support is explicitly not planned for these modules (which means that you should move away from these):

* nodequeue
* nodereference

If you have requests for us to take a field type or entity and make sure it works with Deploy, please add that to the pfizer_deploy issue queue here on github.
