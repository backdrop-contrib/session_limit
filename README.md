Session limit
=============

Limit the number of simultaneous sessions users may have. Limits can be applied by role and per account.

Configuration
-------------

The default maximum number of permitted sessions is 1 per account. Change default max sessions can be changed in
'Configuration >> User accounts >> Session Limit'. The path for this is /admin/config/people/session-limit.

The precedence of defined session limits are:

1. The user's session limit if set, otherwise,
2. The highest session limit for a user as set on their roles, if all are set to default then
3. The system default session_limit.

Optional
--------

This module is able to use the token module for generating tokenized emails or showing tokenized messages on the collision and disconnect events.

https://github.com/backdrop-contrib/token

Current Maintainer
------------------

- David Norman (https://github.com/deekayen)

Credits
-------

- Originally written for Drupal by Cainan (https://www.drupal.org/user/25977)
- Ported to Backdrop by David Norman (https://github.com/deekayen)

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
