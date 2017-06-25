Session limit
=============

Limit the number of simultaneous sessions users may have. Limits can be applied by role and per account.

Force users to log out of any extra sessions after they exceed the administrator-defined maximum.

Features
--------

* On login, logout the oldest session without prompting (optional)
* At login, prevent login if existing session exists elsewhere (optional)
* Notify old session about disconnect
* Configure any number of max allowed sessions
* Configure session limiting exclusions by role
* Configure session limiting exclusions by user
* New user session prompted to select which session to disconnect
* Implements hook on collision
* Implements hook on disconnect
* Integrates with [token module](https://github.com/backdrop-contrib/token)
* Disregard [Masquerade](https://github.com/backdrop-contrib/masquerade)d user sessions in max session counter (optional)

Configuration
-------------

The default maximum number of permitted sessions is 1 per account. Change default max sessions can be changed in
'Configuration >> User accounts >> Session Limit'. The path for this is /admin/config/people/session-limit.

The precedence of defined session limits are:

1. The user's session limit if set, otherwise,
2. The highest session limit for a user as set on their roles, if all are set to default then
3. The system default session_limit.

Other recommended modules
-------------------------

* [Autologout](https://github.com/backdrop-contrib/autologout) - For limiting the length of time a user's session can last.
* [Passphrase Policy](https://github.com/backdrop-contrib/passphrase_policy) - For enforcing password length and complexity.

Current Maintainer
------------------

- None

Credits
-------

- Originally written for Drupal by Cainan (https://www.drupal.org/user/25977)
- Ported to Backdrop by David Norman (https://github.com/deekayen)

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
