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

static void mul_q(int* a, int* b, int* c, int* d) {
    int A = *a + *b,
        B = *a,
        C = *c + *d,
        D = *c;
    *a = A; *b = B; *c = C; *d=D;
}

int fib(int n) {
    if (n == 0) {
        return 0;
    }
    int a = 1, b = 1, c = 1, d = 0;
    for (int i = 1; i < n; ) {
        if (i+i < n) {
            square(&a,&b,&c,&d);
            i += i;
        } else {
            mul_q(&a,&b,&c,&d);
            i += 1;
        }
    }
    return b;
}
