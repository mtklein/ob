`ob`, opinionated build
=======================

`ob` builds C programs if they are structured in its opinionated way.

To bootstrap:

    mkdir -p bin; cc ob.c -o bin/ob

To build in default mode:

    bin/ob

To build in debug, release, ASAN, or TSAN mode:

    bin/ob [--debug|--release|--asan|--tsan]

To print this help:

    bin/ob --help

Any other flags are passed to Ninja.
