`ob`, opinionated build
=====================

`ob` builds C programs if they are structured in its opinionated way.

To bootstrap:

    $ ninja

To use in dev mode:

    $ bin/ob > build.ninja

To use in debug mode:

    $ bin/ob -d > build.ninja

To use in release mode:

    $ bin/ob -r > build.ninja
