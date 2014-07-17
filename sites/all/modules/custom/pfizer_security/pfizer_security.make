; Drush make file for pfizer_security dependencies.

api = 2
core = "7.x"

projects[] = drupal

projects[antivirus][subdir] = "security"
projects[antivirus][version] = "1.0-alpha3"

projects[autologout][subdir] = "security"
projects[autologout][version] = "4.3"

projects[email_confirm][subdir] = "security"
projects[email_confirm][version] = "1.1"

projects[flood_control][subdir] = "security"
projects[flood_control][version] = "1.0"

projects[hacked][subdir] = "security"
projects[hacked][version] = "2.0-beta5"

projects[m4032404][subdir] = "contrib"
projects[m4032404][version] = "1.0-beta2"

projects[mollom][subdir] = "security"
projects[mollom][version] = "2.9"

projects[paranoia][subdir] = "security"
projects[paranoia][version] = "1.3"
; https://drupal.org/node/1813590
; projects[paranoia][patch][i1813590][url] = "http://drupal.org/files/1813590_module_page_structures_3.patch"
; projects[paranoia][patch][i1813590][md5] = "c75e0b82f24a37d558f71cb6772c2085"

projects[password_policy][subdir] = "security"
projects[password_policy][version] = "2.0-alpha1"

projects[seckit][subdir] = "security"
projects[seckit][version] = "1.8"

projects[securepages][subdir] = "security"
projects[securepages][version] = "1.0-beta2"

projects[security_review][subdir] = "security"
projects[security_review][version] = "1.1"

projects[session_limit][subdir] = "security"
projects[session_limit][version] = "2.0"

projects[username_enumeration_prevention][subdir] = "security"
projects[username_enumeration_prevention][version] = "1.0"
