`ob`, opinionated build
=======================

`ob` builds C programs if they are structured in its opinionated way.

To bootstrap:

    mkdir -p bin; cc ob.c -o bin/ob

To build in default mode:

    bin/ob

To build in debug mode:

    bin/ob --debug

To build in release mode:

    bin/ob --release

To print this help:

    bin/ob --help

Any other flags are passed to Ninja.
