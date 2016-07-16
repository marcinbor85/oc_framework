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

struct OC_TestObject {
    OC_NEW_CLASS;
    int var;
};

static void method_set(void *_self, int _i) {
    struct OC_TestObject *self = _self;
    self->var = _i;
}

static void *OC_TestObject_ctor(void *_self, va_list *_args) {
    struct OC_TestObject *self = _self;
    self->var = (int)va_arg(*_args, int);
    return self;
}

static void *OC_TestObject_dtor(void *_self) {
    struct OC_TestObject *self = _self;
    self->var = 0;
    return self;
}

static const struct OC_Class _OC_TestObject = {sizeof(struct OC_TestObject), OC_TestObject_ctor, OC_TestObject_dtor, NULL};
static const void * OC_TestObject = &_OC_TestObject;

/* ************************************************ */

struct OC_ExtendedTestObject {
    OC_NEW_CLASS_EXTENDS(OC_TestObject);
    int var2;
};

static void *OC_ExtendedTestObject_ctor(void *_self, va_list *_args) {
    struct OC_ExtendedTestObject *self = OC_NEW_SUPER_CTOR(OC_TestObject, _self, _args);
    self->var2 = (int)va_arg(*_args, int);
    return self;
}

static void *OC_ExtendedTestObject_dtor(void *_self) {
    struct OC_ExtendedTestObject *self = OC_NEW_SUPER_DTOR(OC_TestObject,_self);
    self->var2 = 0;
    return self;
}

static const struct OC_Class _OC_ExtendedTestObject = {sizeof(struct OC_ExtendedTestObject), OC_ExtendedTestObject_ctor, OC_ExtendedTestObject_dtor, NULL};
static const void * OC_ExtendedTestObject = &_OC_ExtendedTestObject;

/* ************************************************ */

static struct OC_TestObject *testObj;
static struct OC_ExtendedTestObject *testExtendedObj;

static int test_ctor(void)
{
    int var = 1234;
    int var2 = 5678;

    testObj=NULL;
    testObj=oc_new(OC_TestObject, var);

    ASSERT(testObj != NULL);
    ASSERT(malloc_usable_size(testObj) >= sizeof(struct OC_TestObject));
    ASSERT(testObj->class == &_OC_TestObject);
    ASSERT(testObj->var == var);

    testExtendedObj = NULL;
    testExtendedObj = oc_new(OC_ExtendedTestObject, var, var2);

    ASSERT(testExtendedObj != NULL);
    ASSERT(malloc_usable_size(testExtendedObj) >= sizeof(struct OC_ExtendedTestObject));
    ASSERT(testExtendedObj->super.class == OC_ExtendedTestObject);
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

