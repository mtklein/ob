#include <stdio.h>
#include <stdlib.h>

static int fib(int n) {
    if (n < 2) {
        return n;
    }
    return fib(n-1) + fib(n-2);
}

int main(int argc, char** argv) {
    int limit = argc > 1 ? atoi(argv[1]) : 10;
    for (int i = 0; i < limit; i++) {
        printf("%d:\t%d\n", i, fib(i));
    }
    return 0;
}
