#include "check.h"
#include "diff.h"
#include <string.h>

int main(void) {
    char l[95], r[95];
    memset(l, 0x42, 95);
    memset(r, 0x47, 95);
    r[0] = 0x42;
    l[2] = 0x47;
    CHECK(diff(l,r,95) == 93);
    return 0;
}
