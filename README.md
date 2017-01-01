`ob`, opinionated build
=======================

`ob` builds C programs if they are structured in its opinionated way.

To build in default mode:

    ob

To build in debug, release, ASAN, or TSAN mode:

    ob [debug|release|asan|tsan]

Any other flags are passed to Ninja.
