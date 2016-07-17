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

#include "oc/oc_new.h"

/* ************************************************ */

struct oc_test_object {
    OC_NEW_CLASS;
    int var;
};

static void method_set(void *_self, int _i)
{
    struct oc_test_object *self = _self;
    self->var = _i;
}

static void *oc_test_object_ctor(void *_self, va_list *_args)
{
    struct oc_test_object *self = _self;
    self->var = (int)va_arg(*_args, int);
    return self;
}

static void *oc_test_object_dtor(void *_self)
{
    struct oc_test_object *self = _self;
    self->var = 0;
    return self;
}

static const struct oc_class _oc_test_object = {sizeof(struct oc_test_object), oc_test_object_ctor, oc_test_object_dtor, NULL};
static const void * oc_test_object = &_oc_test_object;

/* ************************************************ */

struct oc_extended_test_object {
    OC_NEW_CLASS_EXTENDS(oc_test_object);
    int var2;
};

static void *oc_extended_test_object_ctor(void *_self, va_list *_args)
{
    struct oc_extended_test_object *self = OC_NEW_SUPER_CTOR(oc_test_object, _self, _args);
    self->var2 = (int)va_arg(*_args, int);
    return self;
}

static void *oc_extended_test_object_dtor(void *_self)
{
    struct oc_extended_test_object *self = OC_NEW_SUPER_DTOR(oc_test_object, _self);
    self->var2 = 0;
    return self;
}

static const struct oc_class _oc_extended_test_object = {sizeof(struct oc_extended_test_object), oc_extended_test_object_ctor, oc_extended_test_object_dtor, NULL};
static const void * oc_extended_test_object = &_oc_extended_test_object;

/* ************************************************ */

static struct oc_test_object *testObj;
static struct oc_extended_test_object *testExtendedObj;

static int test_ctor(void)
{
    int var = 1234;
    int var2 = 5678;

    testObj=NULL;
    testObj=oc_new(oc_test_object, var);

    ASSERT(testObj != NULL);
    ASSERT(malloc_usable_size(testObj) >= sizeof(struct oc_test_object));
    ASSERT(testObj->class == &_oc_test_object);
    ASSERT(testObj->var == var);

    testExtendedObj = NULL;
    testExtendedObj = oc_new(oc_extended_test_object, var, var2);

    ASSERT(testExtendedObj != NULL);
    ASSERT(malloc_usable_size(testExtendedObj) >= sizeof(struct oc_extended_test_object));
    ASSERT(testExtendedObj->super.class == oc_extended_test_object);
    ASSERT(testExtendedObj->super.var == var);
    ASSERT(testExtendedObj->var2 == var2);

    return 0;
}

static int test_method(void)
{
    int var = 9999;

    method_set(testObj,var);
    method_set(testExtendedObj,var);

    ASSERT(testObj->var == var);
    ASSERT(testExtendedObj->super.var == var);

    return 0;
}

static int test_dtor(void)
{
    oc_delete(testObj);
    oc_delete(testExtendedObj);

    return 0;
}

int test_oc_new_inherit_all_tests(void)
{
    VERIFY(test_ctor);
    VERIFY(test_method);
    VERIFY(test_dtor);

    return 0;
}

