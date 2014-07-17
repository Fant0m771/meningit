; Drush make file for pfizer_administration dependencies.

api = 2
core = "7.x"

projects[] = drupal

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.0-rc4"

projects[module_filter][subdir] = "contrib"
projects[module_filter][version] = "2.0-alpha2"
; http://drupal.org/node/1933384
; projects[module_filter][patch][i1933384][url] = "http://drupal.org/files/jquery-ui-button-makes-module-filter-fail-1933384-2.patch"
; projects[module_filter][patch][i1933384][md5] = "06e5f34c68244e95ad3f01619870b731"

projects[site_verify][subdir] = "contrib"
projects[site_verify][version] = "1.1"

projects[shiny][type] = "theme"
projects[shiny][version] = "1.4"
projects[shiny][download][type] = get
projects[shiny][download][url] = "http://ftp.drupal.org/files/projects/shiny-7.x-1.4.tar.gz"

