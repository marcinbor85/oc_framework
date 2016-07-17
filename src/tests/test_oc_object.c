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

#include <oc/object.h>

/* ************************************************ */

struct oc_extended_test_object {
    OC_NEW_CLASS_EXTENDS(oc_object);
    int var;
};

static char* to_string(void *_self)
{
    struct oc_extended_test_object *self = _self;
    char *text;
    const char *example = "to_string";
    text = malloc(strlen(example));
    strcpy(text,example);
    return text;
}

static int lock(void *_self)
{
    struct oc_extended_test_object *self = _self;
    self->var = 1;
    return 0;
}

static int unlock(void *_self)
{
    struct oc_extended_test_object *self = _self;
    self->var = 2;
    return 0;
}

static int is_locked(void *_self)
{
    struct oc_extended_test_object *self = _self;
    return self->var;
}

static const struct oc_object_vtable _vtable = { .to_string = to_string, .lock = lock, .unlock = unlock, .is_locked = is_locked };

static void *ctor(void *_self, va_list *_args)
{
    struct oc_extended_test_object *self = OC_NEW_SUPER_CTOR(oc_object, _self, _args);
    self->super.vtable = (struct oc_object_vtable*)&_vtable;
    self->var = 0;
    return self;
}

static void *dtor(void *_self)
{
    struct oc_extended_test_object *self = OC_NEW_SUPER_DTOR(oc_object,_self);
    self->var = 0;
    return self;
}

static const struct oc_class _oc_extended_test_object = {sizeof(struct oc_extended_test_object), "oc_extended_test_object", ctor, dtor, NULL};
static const void * oc_extended_test_object = &_oc_extended_test_object;

/* ************************************************ */

static struct oc_object *testObj;
static struct oc_extended_test_object *testExtendedObj;

static int test_start(void)
{
    testObj=NULL;
    testObj=oc_new(oc_object);

    ASSERT(testObj != NULL);

    testExtendedObj=NULL;
    testExtendedObj=oc_new(oc_extended_test_object);

    ASSERT(testExtendedObj != NULL);

    return 0;
}

static int test_object(void)
{
    char *text;
    int i;

    text = oc_object_to_string(testObj);
    ASSERT(strcmp(text, "oc_object") == 0);
    free(text);

    i = oc_object_lock(testObj);
    ASSERT(i == 0);

    i = oc_object_is_locked(testObj);
    ASSERT(i != 0);

    i = oc_object_lock(testObj);
    ASSERT(i != 0);

    i = oc_object_is_locked(testObj);
    ASSERT(i != 0);

    i = oc_object_unlock(testObj);
    ASSERT(i == 0);

    i = oc_object_is_locked(testObj);
    ASSERT(i == 0);

    text = oc_object_to_string(testExtendedObj);
    ASSERT(strcmp(text, "to_string") == 0);
    free(text);

    i = oc_object_lock(testExtendedObj);
    ASSERT(i == 0);
    ASSERT(testExtendedObj->var == 1);

    i = oc_object_unlock(testExtendedObj);
    ASSERT(i == 0);
    ASSERT(testExtendedObj->var == 2);

    i = oc_object_is_locked(testExtendedObj);
    ASSERT(i == 2);

    testExtendedObj->super.vtable = NULL;

    text = oc_object_to_string(testExtendedObj);
    ASSERT(strcmp(text, "oc_extended_test_object") == 0);
    free(text);
    
    i = oc_object_lock(testExtendedObj);
    ASSERT(i == 0);
    ASSERT(testExtendedObj->var == 2);

    i = oc_object_is_locked(testExtendedObj);
    ASSERT(i != 0);

    i = oc_object_lock(testExtendedObj);
    ASSERT(i != 0);

    i = oc_object_is_locked(testExtendedObj);
    ASSERT(i != 0);

    i = oc_object_unlock(testExtendedObj);
    ASSERT(i == 0);

    i = oc_object_is_locked(testExtendedObj);
    ASSERT(i == 0);

    return 0;
}

static int test_stop(void)
{
    ASSERT(testObj != NULL);
    oc_delete(testObj);
    ASSERT(testObj == NULL);

    ASSERT(testExtendedObj != NULL);
    oc_delete(testExtendedObj);
    ASSERT(testExtendedObj == NULL);

    return 0;
}

int test_oc_object_all_tests(void)
{
    VERIFY(test_start);
    VERIFY(test_object);
    VERIFY(test_stop);

    return 0;
}

