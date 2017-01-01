#pragma once

#include <stdio.h>
#include <stdlib.h>

#define CHECK(cond) \
    do { if (!(cond)) { fprintf(stderr, "%s failed\n", #cond); exit(1); } } while(0)
