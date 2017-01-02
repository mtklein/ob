#include "check.h"
#include <dlfcn.h>
#include <stdint.h>
#include <string.h>

typedef uint32_t (adler32_fn)(uint32_t, const uint8_t*, unsigned);

int main(void) {
    void* zlib = NULL;
    if (!zlib) { zlib = dlopen("libz.so",    RTLD_LAZY); }
    if (!zlib) { zlib = dlopen("libz.dylib", RTLD_LAZY); }
    CHECK(zlib);

    adler32_fn* adler32 = (adler32_fn*)dlsym(zlib, "adler32");
    CHECK(adler32);

    const char* msg = "Hello, world!";
    CHECK(0x20510489 == adler32(0, (const uint8_t*)msg, (unsigned)strlen(msg)));

    return 0;
}
