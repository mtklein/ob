#include "check.h"
#include <stdint.h>
#include <string.h>
#include <zlib.h>  // ob link -lz

int main(void) {
    const char* msg = "Hello, world!";
    CHECK(0x20510489 == adler32(0, (const uint8_t*)msg, (unsigned)strlen(msg)));
    return 0;
}
