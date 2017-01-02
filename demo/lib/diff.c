#include "../cpu_supports.h"
#include "diff.h"
#include <immintrin.h>
#include <string.h>

static int diff_portable(const char* l, const char* r, int n) {
    int diffs = 0;
    while (n --> 0) {
        diffs += (*l++ != *r++);
    }
    return diffs;
}

__attribute__((target("avx2")))
static int diff_avx2(const char* l, const char* r, int n) {
    int diffs = 0;
    while (n >= 32) {
        __m256i L,R;
        memcpy(&L, l, 32);
        memcpy(&R, r, 32);
        int eq_mask = _mm256_movemask_epi8(_mm256_cmpeq_epi8(L, R));
        diffs += 32 - __builtin_popcount((unsigned)eq_mask);
        l += 32;
        r += 32;
        n -= 32;
    }
    return diffs + diff_portable(l,r,n);
}

int diff(const void* l, const void* r, int n) {
    return (cpu_supports_avx2() ? diff_avx2 : diff_portable)(l,r,n);
}
