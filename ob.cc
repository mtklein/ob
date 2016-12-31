#include <stdio.h>
#include <string.h>

struct Options {
    enum { Dev, Debug, Release } build_type;
};
static void set_debug  (Options* o) { o->build_type = Options::Debug;   }
static void set_release(Options* o) { o->build_type = Options::Release; }


static constexpr struct Flag {
    char        brief;
    const char* full;
    void (*callback)(Options*);
} kFlags[] = {
    { 'd', "debug",   set_debug   },
    { 'r', "release", set_release },
};

int main(int argc, char** argv) {
    Options options {
        Options::Dev,
    };

    for (int i = 1; i < argc; i++) {
        for (auto&& flag : kFlags) {
            auto len = strlen(argv[i]);
            if (len == 2 && argv[i][0] == '-'
                         && argv[i][1] == flag.brief) {
                flag.callback(&options);
            }
            if (len >  2 && argv[i][0] == '-'
                         && argv[i][1] == '-'
                         && 0 == strcmp(argv[i]+2, flag.full)) {
                flag.callback(&options);
            }
        }
    }

    const char* targets[] = { "ob" };
    const char*   mains[] = { "ob" };


    printf("rule ob\n");
    printf("    command = $in");
    switch (options.build_type) {
        case Options::Dev:                    break;
        case Options::Debug:   printf(" -d"); break;
        case Options::Release: printf(" -r"); break;
    }
    printf(" > $out\n");

    printf("build build.ninja: ob bin/ob\n");
    printf("    generator = 1\n\n");

    printf("builddir = obj\n");
    printf("cxx      = clang++ -fcolor-diagnostics\n");
    printf("cflags   = -std=c++14");
    if (options.build_type != Options::Release) {
        printf(" -g -Werror -Weverything -Wno-c++98-compat -Wno-padded");
    }
    if (options.build_type != Options::Debug) {
        printf(" -Os");
    }
    printf("\n\n");

    printf("rule compile\n"
           "    command     = $cxx $cflags -MD -MF $out.d -c $in -o $out\n"
           "    depfile     = $out.d\n"
           "    deps        = gcc\n"
           "    description = compile $out\n"
           "\n"
           "rule link\n"
           "    command     = $cxx $in -o $out\n"
           "    description = link $out\n\n");

    for (auto&& target : targets) {
        printf("build obj/%s.o: compile %s.cc\n", target, target);
    }
    printf("\n");

    for (auto&& target : mains) {
        printf("build bin/%s: link obj/%s.o\n", target, target);
    }

    return 0;
}
