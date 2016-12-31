`ob`, opinionated build
=====================

`ob` builds C programs if they are structured in its opinionated way.

To bootstrap:

    $ mkdir -p bin; clang ob.c -o bin/ob

To use in dev mode:

    $ bin/ob; ninja

To use in debug mode:

    $ bin/ob -d; ninja

To use in release mode:

    $ bin/ob -r; ninja
