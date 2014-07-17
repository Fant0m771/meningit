; Drush make file for pfizer_deploy dependencies.

api = 2
core = "7.x"

projects[] = drupal

; Currently we pull the "deploy-revisions" branch of deploy
; Once this is rolled and these patches are rolled into deploy we will revisit
projects[deploy][subdir] = "contrib"
projects[deploy][download][type] = "git"
projects[deploy][download][url] = "http://git.drupal.org/project/deploy.git"
projects[deploy][download][branch] = "deploy-services"
projects[deploy][patch][i2196109][url] = "http://drupal.org/files/issues/deploy-views_missing_revision_id-2196109-2.patch"
projects[deploy][patch][i2196109][md5] = "205f83593700418d738a263621ecb34f"
projects[deploy][patch][i2243537][url] = "http://drupal.org/files/issues/deploy-auto_entity_chooser.patch"
projects[deploy][patch][i2243537][md5] = "88ac1b2fe3f57fd933606d1dcbce4c64"

projects[diff][subdir] = "contrib"
projects[diff][version] = "3.2"

projects[entity_dependency][subdir] = "contrib"
projects[entity_dependency][download][type] = "git"
projects[entity_dependency][download][url] = "http://git.drupal.org/project/entity_dependency.git"
projects[entity_dependency][download][revision] = "043c0903bf3461cf92f8e7cda1723d6ea5c250af"
; https://drupal.org/node/1538848 - deals with malformed or missing entities
projects[entity_dependency][patch][i1538848][url] = "http://drupal.org/files/1538848-missing-bundle-property-5.patch"
projects[entity_dependency][patch][i1538848][md5] = "4531dbecec16e66ca8e1a73147c3fd60"

projects[entity_menu_links][subdir] = "contrib"
projects[entity_menu_links][download][type] = "git"
projects[entity_menu_links][download][url] = "http://git.drupal.org/project/entity_menu_links.git"
projects[entity_menu_links][download][revision] = "f712798"

projects[services][subdir] = "contrib"
projects[services][version] = "3.7"

projects[services_basic_auth][subdir] = "contrib"
projects[services_basic_auth][version] = "1.1"

projects[stage_file_proxy][subdir] = "contrib"
projects[stage_file_proxy][version] = "1.4"

projects[uuid][subdir] = "contrib"
projects[uuid][download][type] = "git"
projects[uuid][download][url] = "http://git.drupal.org/project/uuid.git"
projects[uuid][download][revision] = "3f4d9fb5e45a147980a89e611f8c124be5c69948"
; http://drupal.org/node/2074599 - remove contrib support from the uuid.core.inc so that it can be included separately
projects[uuid][patch][] = "http://drupal.org/files/uuid_remove_contrib_support-2074599-2.patch"
; field collection - patch uuid services to not check access callback for field collections
; need a better way to do this but for now:
projects[uuid][patch][] = "http://drupal.org/files/uuid_services_field_collection_revisions.patch"
; https://drupal.org/node/1209726 - this was a features related patch for menus
; projects[uuid][patch][] = "http://drupal.org/files/uuid-menus-1209726-2.patch"

