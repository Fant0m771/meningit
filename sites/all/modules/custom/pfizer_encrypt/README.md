Pfizer Encrypt Feature
==============

##1. Introduction#

> This feature aggregates three important modules (Encrypt, Field Encrypt and Webform Encrypt) that are foundation to encrypting PII data in Drupal sites. It also provides a custom Pfizer-specific encryption mechanism and automatically configures Encrypt to use it as default.

##2. What data to encrypt#

> Pfizer’s policy determines that PII (Personally identifiable information) should always be encrypted. That entails any information that can identify a user, e.g. SSN, first and last name, e-mail, and so forth.

##3. Encrypting data in Drupal#

> ###3.1 Modules#
> > > ####3.1.1 Encrypt#
> > > > Encrypt is a module that provides an easy-to-use two-way encryption API. It’s the foundation and pre-requisite of the modules below. It doesn’t provide any functionality by itself out of the box, but it’s a dependency module that needs to be configured for other modules to work, and it can also be used to encrypt custom implementations data.

> > > ####3.1.2 Field Encrypt#
> > > > The goal of Field Encrypt is to easily encrypt field data in Drupal. It depends on Encrypt module and makes it simple to individually select which fields need to be encrypted. It creates a separate table to store encrypted data, and it encrypts/decrypts data on load/save.

> > > ####3.1.3 Webform Encrypt#
> > > > This module provides the ability to encrypt fields/components part of the Webform module. All submitted data that is marked to be encrypted goes through Webform Encrypt, which encrypts it prior to saving and decrypts it right after loading from the database.

> ###3.2 Using Field Encrypt to encrypt fields#
> > An easy solution to encrypt fields such as the ones found in content types, user entity, and so forth is to utilize the module Field Encrypt. Perhaps the most common use case for this module is to encrypt users identifiable information in their profile. This can easily be done by executing the following steps:
> > > 1.  Go to your content type (admin/structure/types), or account settings page (admin/config/people/accounts).
> > > 2.  Click on manage fields.
> > > 3.  Go to the edit page of the field that needs to be encrypted.
> > > 4.  Check the "Encrypt this field" box under Global Settings -> Encrypt this field.
> > > 5.  Save settings.

> ###3.3 Using Webform Encrypt to encrypt webform fields#
> > Similarly to Field Encrypt, this module provides a checkbox for each field/component part making it really straightforward to enable encryption for webform PII data, as shown on the steps below:
> > > 1.  Go to your webform edit page.
> > > 2.  Click on webform tab.
> > > 3.  Go to the edit page of the field that needs to be encrypted.
> > > 4.  Check the "Encrypt this field's value" box under Encryption.
> > > 5.  Save component.

##4. Caveats#
> Our current encryption mechanism relies on a key provided by Acquia which changes across sites. This means that this key is not available in environments outside Acquia (e.g. local boxes) infrastructure and a default key is used. As result of that, encrypted content promoted from local boxes to Acquia environments will not be able to be decrypted. However, this shouldn't be a problem as PII data shouldn't come from non-Acquia environments.
