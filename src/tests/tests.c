/*
The MIT License (MIT)

Copyright (c) 2016 Marcin Borowicz <marcinbor85@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "tests.h"

int tests_run = 0;

extern int test_oc_new_all_tests(void);
extern int test_oc_new_singleton_all_tests(void);
extern int test_oc_new_inherit_all_tests(void);
extern int test_oc_new_vtable_all_tests(void);

extern int test_oc_object_all_tests(void);
extern int test_oc_queue_all_tests(void);
extern int test_oc_fifo_all_tests(void);
extern int test_oc_lifo_all_tests(void);
extern int test_oc_list_all_tests(void);
extern int test_oc_chardev_all_tests(void);

static int all_tests(void)
{
    INCLUDE(test_oc_new_all_tests);
    INCLUDE(test_oc_new_singleton_all_tests);
    INCLUDE(test_oc_new_inherit_all_tests);
    INCLUDE(test_oc_new_vtable_all_tests);

    INCLUDE(test_oc_object_all_tests);
    INCLUDE(test_oc_queue_all_tests);
    INCLUDE(test_oc_fifo_all_tests);
    INCLUDE(test_oc_lifo_all_tests);
    INCLUDE(test_oc_list_all_tests);
    INCLUDE(test_oc_chardev_all_tests);

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


