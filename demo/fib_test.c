#include "lib/fib.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK(cond) \
    do { if (!(cond)) { fprintf(stderr, "%s failed\n", #cond); exit(1); } } while(0)

int main(void) {
    CHECK(fib(0) == 0);
    CHECK(fib(1) == 1);
    CHECK(fib(2) == 1);
    CHECK(fib(3) == 2);
    CHECK(fib(4) == 3);
    CHECK(fib(5) == 5);
    CHECK(fib(6) == 8);
    return 0;
}
