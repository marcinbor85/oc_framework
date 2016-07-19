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

#include <oc/chardev.h>

static struct oc_chardev *testDev;

static int test_start(void)
{
    testDev = NULL;
    testDev = oc_new(oc_chardev);

    ASSERT(testDev != NULL);
    ASSERT(testDev->input != NULL);
    ASSERT(testDev->output != NULL);

    return 0;
}

static int test_method(void)
{
    char *text;
    int s;

    text = oc_object_to_string(testDev);
    ASSERT(strcmp(text, "oc_chardev") == 0);
    free(text);

    return 0;
}

static int test_stop(void)
{
    ASSERT(testDev != NULL);
    oc_delete(testDev);
    ASSERT(testDev == NULL);

    return 0;
}

int test_oc_chardev_all_tests(void)
{
    VERIFY(test_start);
    VERIFY(test_method);
    VERIFY(test_stop);

    return 0;
}

