`ob`, opinionated build
=======================

`ob` builds C programs if they are structured in its opinionated way:
- each `#include` within the project is source-relative;
- each `foo.c` defines `int main(...)` or has a corresponding `foo.h`.

To build in default mode:

    ob

To build in debug, release, ASAN, or TSAN mode:

    ob [-D|--debug] [-R|--release] [-A|--asan] [-T|--tsan]

Any other flags and arguments are passed to Ninja.
