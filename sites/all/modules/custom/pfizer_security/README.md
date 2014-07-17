pfizer_security
===============

Pfizer Security Core Feature

This feature includes several modules that are either enforced at build time or required to obtain
approval from Pfizer's security team. This feature depends on very specific versions of several
modules:

* antivirus
* autologout
* flood_control
* hacked
* m4032404
* mollom
* paranoia
* password_policy
* seckit
* securepages
* security_review
* session_limit

###Auto Logout:
This module limits sessions to 15 minutes and auto-logs out a user after that period of time.  A JS pop up offers to allow the user to continue their session, and if not clicked, the user is logged out of the site with a message stating they have been logged out due to inactivity.

###Mollom:
Mollom is a web service that analyzes the quality of content posted to websites and tries to
determine whether this content is spam or not. This service should replace captcha for sites with
low traffic. To use this module, please request a key pair to the support team at:
DL-BT-DIGITALMARKETING@pfizer.com.

###Paranoia:
The Paranoia module attempts to identify all the places that a user can evaluate PHP via Drupal's
web interface and then block those. It reduces the potential impact of an attacker gaining
elevated permission on a Drupal site. This module will be enforced at build time in the near feature
and phpfilter will not work in Pfizer's platform.

###Secure Pages:
This module is turned on and configured at build time. Site-specific configurations will be appended
to Pfizer's standard configurations and SSL will be enforced for a pre-defined set of URLs.

###Security Kit:
This module sets sensible defaults for http headers related to security.  You can customize this to enable sites to be loaded in an iframe for instance at the settings page located at /admin/config/system/seckit.

###Session Limit:
This module prevents simultaneous logins with the same username.  The oldest session is logged off automatically if the user logs in from another location.

###Additional Features:

This feature also provides some additional functions:

* It adds the ability to deny all login to the site except for using drush's uli command.  You can enable this by setting the deny_login variable to TRUE.
* It provides some logic to render a not found page when a user hits node/123/whatever-you-type.something
* Checks file uploads for consistency between name-based MIME type and content-based MIME type.
