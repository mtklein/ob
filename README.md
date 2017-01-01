`ob`, opinionated build
=======================

`ob` builds C and C++ programs with Ninja if they are structured in its opinionated way:
- each source file is tracked in Git;
- each `#include` within the project is source-relative;
- each `foo.c` or `foo.cc` defines `int main(...)` or has a corresponding `foo.h`;
- each `foo_test.c` or `foo_test.cc` is a unit test that is expected to return 0.

To build in default mode:

    ob

To build in debug, release, ASAN, or TSAN mode:

    ob [-D|--debug] [-R|--release] [-A|--asan] [-T|--tsan]

Any other command line flags or arguments are passed to Ninja.

`ob` recognizes the following environment variables:
`CC`, `CXX`, `CPPFLAGS`, `CFLAGS`, `CXXFLAGS`, `LDFLAGS`.
