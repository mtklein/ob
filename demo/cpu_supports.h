#pragma once

static inline int cpu_supports_avx2() {
#if defined(__x86_64h__)
    return 1;
#elif !defined(__clang__)
    return __builtin_cpu_supports("avx2");
#else
    return 0;
#endif
}

static inline int cpu_supports_bmi() {
#if defined(__x86_64h__)
    return 1;
#elif !defined(__clang__)
    return __builtin_cpu_supports("bmi");
#else
    return 0;
#endif
}

