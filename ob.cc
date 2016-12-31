#include <stdio.h>
#include <string.h>

enum class BuildType { Dev, Debug, Release };

int main(int argc, char** argv) {
    auto build_type = BuildType::Dev;

    for (int i = 1; i < argc; i++) {
        if (0 == strcmp(argv[i], "-d") || 0 == strcmp(argv[i], "--debug")) {
            build_type = BuildType::Debug;
        }
        if (0 == strcmp(argv[i], "-r") || 0 == strcmp(argv[i], "--release")) {
            build_type = BuildType::Release;
        }
    }

    const char* targets[] = { "ob" };
    const char*   mains[] = { "ob" };


    printf("rule ob\n");
    printf("    command = $in");
    switch (build_type) {
        case BuildType::Dev:                    break;
        case BuildType::Debug:   printf(" -d"); break;
        case BuildType::Release: printf(" -r"); break;
    }
    printf(" > $out\n");

    printf("build build.ninja: ob bin/ob\n");
    printf("    generator = 1\n\n");

    printf("builddir = obj\n");
    printf("cxx      = clang++ -fcolor-diagnostics\n");
    printf("cflags   = -std=c++14");
    if (build_type != BuildType::Release) {
        printf(" -g -Werror -Weverything -Wno-c++98-compat -Wno-padded");
    }
    if (build_type != BuildType::Debug) {
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
