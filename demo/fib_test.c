#include "check.h"
#include "lib/fib.h"

int main(void) {
    CHECK(fib(0) == 0);
    CHECK(fib(1) == 1);
    CHECK(fib(2) == 1);
    CHECK(fib(3) == 2);
    CHECK(fib(4) == 3);
    CHECK(fib(5) == 5);
    CHECK(fib(6) == 8);
    CHECK(fib(7) == 13);
    CHECK(fib(8) == 21);
    CHECK(fib(9) == 34);
    return 0;
}
