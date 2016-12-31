#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum BuildType { kDefault, kDebug, kRelease, kASAN, kTSAN };

static void write_ninja(const char* path, enum BuildType bt) {
    FILE* ninja = fopen(path, "w");
    fprintf(ninja, "builddir = obj\n"
                   "rule cc\n"
                   "    command     = $cc $cflags -MD -MF $out.d -c $in -o $out\n"
                   "    depfile     = $out.d\n"
                   "    deps        = gcc\n"
                   "    description = compile $out\n"
                   "rule link\n"
                   "    command     = $cc $in -o $out\n"
                   "    description = link $out\n");

    fprintf(ninja, "cc = clang");
    if (bt == kASAN)    { fprintf(ninja, " -fsanitize=address,undefined"); }
    if (bt == kTSAN)    { fprintf(ninja, " -fsanitize=thread"); }
    if (bt == kRelease) { fprintf(ninja, " -flto=thin"); }
    fprintf(ninja, "\n");

    fprintf(ninja, "cflags = -fcolor-diagnostics");
    if (bt != kDebug)   { fprintf(ninja, " -Os"); }
    if (bt != kRelease) { fprintf(ninja, " -g -Werror -Weverything -Wno-padded"); }
    if (bt == kRelease) { fprintf(ninja, " -DNDEBUG"); }
    fprintf(ninja, "\n");

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
}

int main(int argc, char** argv, char** envp) {
    enum BuildType bt = kDefault;

    char** ninja_argv = calloc((size_t)argc+1, sizeof(char*));
    char** np = ninja_argv;
    *np++ = "ninja";

    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "--debug"))   { bt = kDebug;   continue; }
        if (0 == strcmp(argv[i], "--release")) { bt = kRelease; continue; }
        if (0 == strcmp(argv[i], "--asan"))    { bt = kASAN;    continue; }
        if (0 == strcmp(argv[i], "--tsan"))    { bt = kTSAN;    continue; }
        if (0 == strcmp(argv[i], "--help")) {
            printf("`ob`, opinionated build\n"
                   "=======================\n\n"
                   "`ob` builds C programs if they are structured in its opinionated way.\n\n"
                   "To bootstrap:\n\n"
                   "    mkdir -p bin; cc ob.c -o bin/ob\n\n"
                   "To build in default mode:\n\n"
                   "    bin/ob\n\n"
                   "To build in debug, release, ASAN, or TSAN mode:\n\n"
                   "    bin/ob [--debug|--release|--asan|--tsan]\n\n"
                   "To print this help:\n\n"
                   "    bin/ob --help\n\n"
                   "Any other flags are passed to Ninja.\n");
            return 1;
        }
        *np++ = argv[i];
    }

    write_ninja("build.ninja", bt);
    {
        pid_t pid;
        posix_spawnp(&pid, "ninja", NULL, NULL, ninja_argv, envp);
        waitpid(pid, NULL, 0);
    }
    remove("build.ninja");
    free(ninja_argv);
    return 0;
}
