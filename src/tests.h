#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>

extern int tests_run;

#define FAIL() printf("\nFailure in %s() line %d\n", __func__, __LINE__)
#define ASSERT(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define VERIFY(test) do { int r=test(); tests_run++; if(r) return r; } while(0)
#define INCLUDE(test) do { int r=test(); if(r) return r; } while(0)

#endif /* TESTS_H */

