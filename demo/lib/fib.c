#include "fib.h"

static void square(int* a, int* b, int* c, int* d) {
    int aa = *a * *a,
        ab = *a * *b,
        ac = *a * *c,
        bc = *b * *c,
        bd = *b * *d,
        cd = *c * *d,
        dd = *d * *d;
    *a = aa + bc;
    *b = ab + bd;
    *c = ac + cd;
    *d = bc + dd;
}

static void mul_1110(int* a, int* b, int* c, int* d) {
    int A = *a + *b,
        B = *a,
        C = *c + *d,
        D = *c;
    *a = A; *b = B; *c = C; *d=D;
}

int fib(int n) {
    int a = 1, b = 1, c = 1, d = 0;

    int i = 1;
    for (; i+i <= n; i += i) { square  (&a,&b,&c,&d); }
    for (;   i <= n; i += 1) { mul_1110(&a,&b,&c,&d); }
    return d;
}
