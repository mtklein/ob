#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum BuildType { kDev, kDebug, kRelease };

int main(int argc, char** argv) {
    enum BuildType bt = kDev;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'd') { bt = kDebug;   }
        if (argv[i][0] == '-' && argv[i][1] == 'r') { bt = kRelease; }
    }

    FILE* ninja = fopen("build.ninja", "w");
    fprintf(ninja, "builddir = obj\n");
    fprintf(ninja, "cc       = clang\n");
    fprintf(ninja, "cflags   = -fcolor-diagnostics");
    if (bt != kRelease) {
        fprintf(ninja, " -g -Werror -Weverything -Wno-padded");
    }
    if (bt != kDebug) {
        fprintf(ninja, " -Os");
    }
    if (bt == kRelease) {
        fprintf(ninja, " -DNDEBUG");
    }
    fprintf(ninja, "\n");

    fprintf(ninja, "rule cc\n"
                   "    command     = $cc $cflags -MD -MF $out.d -c $in -o $out\n"
                   "    depfile     = $out.d\n"
                   "    deps        = gcc\n"
                   "    description = compile $out\n"
                   "rule link\n"
                   "    command     = $cc $in -o $out\n"
                   "    description = link $out\n\n");

    const char* srcs[] = { "hello", "ob" };
    int nsrcs = sizeof(srcs) / sizeof(*srcs);
    for (int i = 0; i < nsrcs; i++) {
        fprintf(ninja, "build obj/%s.o: cc %s.c\n", srcs[i], srcs[i]);
    }

    const char* mains[] = { "hello", "ob" };
    int nmains = sizeof(srcs) / sizeof(*mains);
    for (int i = 0; i < nmains; i++) {
        fprintf(ninja, "build bin/%s: link obj/%s.o\n", mains[i], mains[i]);
    }

    fclose(ninja);

    system("ninja");
    remove("build.ninja");
    return 0;
}
