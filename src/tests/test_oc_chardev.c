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

/* ************************************************ */

static int checker;

struct oc_test_chardev {
    OC_NEW_CLASS_EXTENDS(oc_chardev);
};

static int put(void *_self, int _stat)
{
    struct oc_test_chardev *self = _self;
    checker = 10+_stat;
    return _stat;
}

static int get(void *_self, int _stat)
{
    struct oc_test_chardev *self = _self;
    checker = 20+_stat;
    return _stat;
}

static const struct oc_chardev_vtable _vtable = { .put_callback = put, .get_callback  = get };

static void *ctor(void *_self, va_list *_args)
{
    struct oc_test_chardev *self = OC_NEW_SUPER_CTOR(oc_chardev, _self, _args);
    self->super.vtable = (struct oc_chardev_vtable*)&_vtable;
    return self;
}

static void *dtor(void *_self)
{
    struct oc_test_chardev *self = OC_NEW_SUPER_DTOR(oc_chardev,_self);
    return self;
}

static const struct oc_class _oc_test_chardev = {sizeof(struct oc_test_chardev), "oc_test_chardev", ctor, dtor, NULL};
static const void * oc_test_chardev = &_oc_test_chardev;

/* ************************************************ */

static struct oc_test_chardev *testDev;

static int test_start(void)
{
    testDev = NULL;
    testDev = oc_new(oc_test_chardev, 4, 4);

    ASSERT(testDev != NULL);
    ASSERT(testDev->super.input != NULL);
    ASSERT(testDev->super.output != NULL);

    return 0;
}

static int test_method(void)
{
    char *text;
    int s;
    char ch;

    text = oc_object_to_string(testDev);
    ASSERT(strcmp(text, "oc_test_chardev") == 0);
    free(text);

    text = oc_object_to_string(testDev->super.input);
    ASSERT(strcmp(text, "oc_fifo") == 0);
    free(text);

    text = oc_object_to_string(testDev->super.output);
    ASSERT(strcmp(text, "oc_fifo") == 0);
    free(text);

    checker = 0;
    s = oc_chardev_get_char(testDev,&ch);
    ASSERT(s == 0);
    ASSERT(checker == 20);

    ch = 100;
    checker = 0;
    s = oc_chardev_put_char(testDev,&ch);
    ASSERT(s == 1);
    ASSERT(checker == 11);

    checker = 0;
    s = oc_chardev_get_char(testDev,&ch);
    ASSERT(s == 0);
    ASSERT(checker == 20);

    s = oc_chardev_pull_output(testDev,&ch);
    ASSERT(s == 1);
    ASSERT(ch == 100);

    s = oc_chardev_pull_output(testDev,&ch);
    ASSERT(s == 0);
    ASSERT(ch == 100);

    ch = 50;
    s = oc_chardev_push_input(testDev,&ch);
    ASSERT(s == 1);
    ASSERT(ch == 50);

    checker = 0;
    s = oc_chardev_get_char(testDev,&ch);
    ASSERT(s == 1);
    ASSERT(checker == 21);
    ASSERT(ch == 50);

    checker = 0;
    s = oc_chardev_get_char(testDev,&ch);
    ASSERT(s == 0);
    ASSERT(checker == 20);
    ASSERT(ch == 50);

    testDev->super.vtable = NULL;

    checker = 40;
    s = oc_chardev_get_char(testDev,&ch);
    ASSERT(s == 0);
    ASSERT(checker == 40);
    ASSERT(ch == 50);

    ch = 1;
    checker = 30;
    s = oc_chardev_put_char(testDev,&ch);
    ASSERT(s == 1);
    ASSERT(checker == 30);
    ASSERT(ch == 1);

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

