; Drush make file for pfizer_authentication modules.

api = 2
core = "7.x"

projects[] = drupal

projects[rpx][subdir] = "contrib"
projects[rpx][version] = "2.2"
; https://drupal.org/node/2174097
projects[rpx][patch][i2174097][url] = "http://drupal.org/files/issues/clearing_cache_after_entity_update-2174097-0.patch"
projects[rpx][patch][i2174097][md5] = "ad7e0e2c89d1c4fef66c0863b87b38ce"

projects[pfizer_auth][type] = "module"
projects[pfizer_auth][subdir] = "custom"
projects[pfizer_auth][download][type] = "git"
projects[pfizer_auth][download][url] = "git@github.com:pfizer/pfizer_auth.git"
projects[pfizer_auth][download][tag] = "7.x-1.0"

projects[pfizer_connect][type] = "module"
projects[pfizer_connect][subdir] = "custom"
projects[pfizer_connect][download][type] = "git"
projects[pfizer_connect][download][url] = "git@github.com:pfizer/pfizer_connect.git"
projects[pfizer_connect][download][tag] = "7.x-1.0"
