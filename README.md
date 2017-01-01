`ob`, opinionated build
=======================

`ob` builds C and C++ programs if they are structured in its opinionated way:
- each `#include` within the project is source-relative;
- each `foo.c` or `foo.cc` defines `int main(...)` or has a corresponding `foo.h`.

To build in default mode:

    ob

To build in debug, release, ASAN, or TSAN mode:

    ob [-D|--debug] [-R|--release] [-A|--asan] [-T|--tsan]

Any other command line flags or arguments are passed to Ninja.

`ob` recognizes the following environment variables:
`CC`, `CXX`, `CPPFLAGS`, `CFLAGS`, `CXXFLAGS`, `LDFLAGS`.

TODO
----
- auto-detect files with `_test` in their name containing `int main(...)`, build, and run them
