Pfizer Administration
=====================

Pfizer Administration Core Feature

This feature is a simple way to add the default Pfizer administration tools.  This feature depends on 4 modules:

* admin_menu
* admin_menu_toolbar
* dashboard
* features
* module_filter
* views

It also disables the core Toolbar module if it's enabled so you can enable it post standard install.

This module also enforces all nodes to create revisions each time the node is updated.
It forces you to add a log message, which then shows on the dashboard view that shows latest updates to the site.

It adds 2 views to the main admin dashboard:

* recently updated content along with the last revision log message
* recently logged in users

We intend for this to be used to tell at a glance who is updating content on a site.
Eventually this functionality will be replaced by the DMP.
