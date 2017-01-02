#pragma once

#include <stdio.h>

#define CHECK(cond) \
    do { if (!(cond)) { fprintf(stderr, "%s failed\n", #cond); __builtin_trap(); } } while(0)
