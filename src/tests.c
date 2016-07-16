#include "tests.h"

#include "oc/oc_new.h"

int tests_run = 0;

extern int test_oc_new_all_tests(void);
extern int test_oc_new_singleton_all_tests(void);
extern int test_oc_new_inherit_all_tests(void);
extern int test_oc_new_vtable_all_tests(void);

static int all_tests(void)
{
    INCLUDE(test_oc_new_all_tests);
    INCLUDE(test_oc_new_singleton_all_tests);
    INCLUDE(test_oc_new_inherit_all_tests);
    INCLUDE(test_oc_new_vtable_all_tests);

    return 0;
}

int main(int argc, char **argv)
{
    int result = all_tests();
    if (result == 0) {
        printf("PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}


