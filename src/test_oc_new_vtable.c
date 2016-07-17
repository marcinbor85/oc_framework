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

struct oc_abstract_test_object_vtable {
    int (*set)(void *, void *);
    int (*get)(void *, void *);
    int (*change)(void *);
};

struct oc_abstract_test_object {
    OC_NEW_CLASS;
    struct oc_abstract_test_object_vtable *vtable;
};

static int method_set(void *_self, void *_i)
{
    struct oc_abstract_test_object *self = _self;
    if (self->vtable == NULL) return -1;
    if (self->vtable->set == NULL) return -1;
    return self->vtable->set(_self, _i);
}

static int method_get(void *_self, void *_i)
{
    struct oc_abstract_test_object *self = _self;
    if (self->vtable == NULL) return -1;
    if (self->vtable->get == NULL) return -1;
    return self->vtable->get(_self, _i);
}

static int method_change(void *_self)
{
    struct oc_abstract_test_object *self = _self;
    if (self->vtable == NULL) return -1;
    if (self->vtable->change == NULL) return -1;
    return self->vtable->change(_self);
}

static void *oc_abstract_test_object_ctor(void *_self, va_list *_args)
{
    struct oc_abstract_test_object *self = _self;
    return self;
}

static void *oc_abstract_test_object_dtor(void *_self)
{
    struct oc_abstract_test_object *self = _self;
    return self;
}

static const struct oc_class _oc_abstract_test_object = {sizeof(struct oc_abstract_test_object), oc_abstract_test_object_ctor, oc_abstract_test_object_dtor, NULL};
static const void * oc_abstract_test_object = &_oc_abstract_test_object;

/* ************************************************ */

struct oc_extended_test_object {
    OC_NEW_CLASS_EXTENDS(oc_abstract_test_object);
    int var;
};

static int _set(void *_self, void *_i)
{
    struct oc_extended_test_object *self = _self;
    self->var = *(int*)_i;
    return 0;
}

static int _get(void *_self, void *_i)
{
    struct oc_extended_test_object *self = _self;
    *(int*)_i = self->var;
    return 0;
}

static const struct oc_abstract_test_object_vtable _vtable = { .set = _set, .get = _get };

static void *oc_extended_test_object_ctor(void *_self, va_list *_args)
{
    struct oc_extended_test_object *self = OC_NEW_SUPER_CTOR(oc_abstract_test_object, _self, _args);
    self->super.vtable = (struct oc_abstract_test_object_vtable*)&_vtable;
    self->var = (int)va_arg(*_args, int);
    return self;
}

static void *oc_extended_test_object_dtor(void *_self)
{
    struct oc_extended_test_object *self = OC_NEW_SUPER_DTOR(oc_abstract_test_object,_self);
    self->var = 0;
    return self;
}

static const struct oc_class _oc_extended_test_object = {sizeof(struct oc_extended_test_object), oc_extended_test_object_ctor, oc_extended_test_object_dtor, NULL};
static const void * oc_extended_test_object = &_oc_extended_test_object;

/* ************************************************ */

static struct oc_extended_test_object *testObj;

static int test_ctor(void)
{
    int var = 1234;

    testObj=NULL;
    testObj=oc_new(oc_extended_test_object, var);

    ASSERT(testObj != NULL);
    ASSERT(malloc_usable_size(testObj) >= sizeof(struct oc_extended_test_object));
    ASSERT(testObj->super.class == oc_extended_test_object);
    ASSERT(testObj->super.vtable == &_vtable);
    ASSERT(testObj->var == var);

    return 0;
}

static int test_method(void)
{
    int var = 9999;
    int ret;
    int s;

    s = method_set(testObj,&var);
    ASSERT(testObj->var == var);
    ASSERT(s == 0);

    s = method_get(testObj,&ret);
    ASSERT(testObj->var == ret);
    ASSERT(testObj->var == var);
    ASSERT(s == 0);

    s = method_change(testObj);
    ASSERT(s != 0);

    return 0;
}

static int test_dtor(void)
{
    ASSERT(testObj != NULL);
    oc_delete(testObj);
    ASSERT(testObj == NULL);

    return 0;
}

int test_oc_new_vtable_all_tests(void)
{
    VERIFY(test_ctor);
    VERIFY(test_method);
    VERIFY(test_dtor);

    return 0;
}

