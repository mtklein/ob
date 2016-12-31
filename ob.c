#include <stdio.h>
#include <string.h>

enum BuildType { kDev, kDebug, kRelease };

int main(int argc, char** argv) {
    enum BuildType bt = kDev;

    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-d")) { bt = kDebug;   }
        if (0 == strcmp(argv[i], "-r")) { bt = kRelease; }
    }

    printf("rule ob\n");
    printf("    command = $in");
    switch (bt) {
        case kDev:                    break;
        case kDebug:   printf(" -d"); break;
        case kRelease: printf(" -r"); break;
    }
    printf(" > $out\n");

    printf("build build.ninja: ob bin/ob\n");
    printf("    generator = 1\n\n");

    printf("builddir = obj\n");
    printf("cc       = clang\n");
    printf("cflags   = -fcolor-diagnostics");
    if (bt != kRelease) {
        printf(" -g -Werror -Weverything -Wno-padded");
    }
    if (bt != kDebug) {
        printf(" -Os");
    }
    if (bt == kRelease) {
        printf(" -DNDEBUG");
    }
    printf("\n");

    printf("rule cc\n"
           "    command     = $cc $cflags -MD -MF $out.d -c $in -o $out\n"
           "    depfile     = $out.d\n"
           "    deps        = gcc\n"
           "    description = compile $out\n"
           "\n"
           "rule link\n"
           "    command     = $cc $in -o $out\n"
           "    description = link $out\n\n");

    const char* srcs[] = { "hello", "ob" };
    int nsrcs = sizeof(srcs) / sizeof(*srcs);
    for (int i = 0; i < nsrcs; i++) {
        printf("build obj/%s.o: cc %s.c\n", srcs[i], srcs[i]);
    }

    const char* mains[] = { "hello", "ob" };
    int nmains = sizeof(srcs) / sizeof(*mains);
    for (int i = 0; i < nmains; i++) {
        printf("build bin/%s: link obj/%s.o\n", mains[i], mains[i]);
    }

    return 0;
}
