// ob compile -mbmi
#include "check.h"
#include "cpu_supports.h"
#include <immintrin.h>
#include <stdint.h>

int main(void) {
    if (cpu_supports_bmi()) {
        uint32_t x = 0x42473211;
        CHECK(0x47 == _bextr_u32(x, 16, 8));
    }
    return 0;
}
