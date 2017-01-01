#pragma once

static inline int avx2_supported() {
#if defined(__AVX2__)
    return 1;
#elif !defined(__clang__)
    return __builtin_cpu_supports("avx2");
#else
    return 0;
#endif
}
