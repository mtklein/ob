#include "check.h"
#include <math.h>

int main(void) {
    for (int i = 0; i < 10; i++) {
        float f = i*i;
        CHECK(sqrtf(f) == (float)i);
    }
    for (int i = 0; i < 10; i++) {
        float f = powf(2, i);
        CHECK(__builtin_popcount((unsigned)f) == 1);
    }
    return 0;
}
