#include "check.h"
#include <immintrin.h>  // ob compile -mbmi
#include <stdint.h>

int main(void) {
    uint32_t x = 0x42473211;
    CHECK(0x47 == _bextr_u32(x, 16, 8));
    return 0;
}
