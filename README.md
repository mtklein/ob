`ob`, opinionated build
=====================

`ob` builds C programs if they are structured in its opinionated way.

To bootstrap:

    $ clang ob.c -o bin/ob

To use in dev mode:

    $ bin/ob > build.ninja

To use in debug mode:

    $ bin/ob [-d|--debug] > build.ninja

To use in release mode:

    $ bin/ob [-r|--release] > build.ninja
