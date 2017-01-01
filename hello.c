#include "src/print_hello.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Hello, World.\n");
    print_hello();
    assert(3 == 4);
    return 0;
}
