`ob`, opinionated build
=====================

`ob` builds C and C++ programs if they are structured in its opinionated way.

To bootstrap:

    $ ninja

To use in dev mode:

    $ bin/ob > build.ninja

To use in debug mode:

    $ bin/ob [-d|--debug] > build.ninja

To use in release mode:

    $ bin/ob [-r|--release] > build.ninja
