// This is a comment.
#include "lib/fib.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int limit = argc > 1 ? atoi(argv[1]) : 10;
    for (int i = 0; i < limit; i++) {
        printf("%d:\t%d\n", i, fib(i));
    }
    return 0;
}
