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

#include "../oc/oc_new.h"

/* ************************************************ */

static struct oc_test_object *_singleton;

struct oc_test_object {
    OC_NEW_CLASS;
    int var;
};

static void *ctor(void *_self, va_list *_args)
{
    struct oc_test_object *self = _self;
    self->var = (int)va_arg(*_args, int);
    return self;
}

static void *dtor(void *_self)
{
    struct oc_test_object *self = _self;
    self->var = 0;
    return self;
}

static const struct oc_class _oc_test_object = {sizeof(struct oc_test_object), "oc_test_object", ctor, dtor, &_singleton};
static const void * oc_test_object = &_oc_test_object;

/* ************************************************ */

static struct oc_test_object *testObj;
static struct oc_test_object *testObj2;

static int test_ctor(void)
{
    int var = 1234;
    int var2 = 5678;

    testObj = NULL;
    testObj = oc_new(oc_test_object, var);

    ASSERT(testObj != NULL);
    ASSERT(malloc_usable_size(testObj) >= sizeof(struct oc_test_object));
    ASSERT(testObj->class == &_oc_test_object);
    ASSERT(testObj->var == var);

    return 0;
}

static int test_object(void)
{
    int var = 1234;
    int var2 = 5678;

    testObj2 = NULL;
    testObj2 = oc_new(oc_test_object, var2);

    ASSERT(testObj2 == testObj);
    ASSERT(testObj2->var == testObj->var);
    ASSERT(testObj2->var == var);

    return 0;
}

static int test_dtor(void)
{
    ASSERT(testObj != NULL);
    oc_delete(testObj);
    ASSERT(testObj == NULL);

    return 0;
}

int test_oc_new_singleton_all_tests(void)
{
    VERIFY(test_ctor);
    VERIFY(test_object);
    VERIFY(test_dtor);

    return 0;
}

