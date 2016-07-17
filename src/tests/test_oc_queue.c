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

#include "../oc/oc_queue.h"

/* ************************************************ */

struct oc_test_queue {
    OC_NEW_CLASS_EXTENDS(oc_queue);
    int var;
};

static int put(void *_self, void *_item)
{
    struct oc_test_queue *self = _self;
    self->var = *(int*)_item;
    return 1;
}

static int get(void *_self, void *_item)
{
    struct oc_test_queue *self = _self;
    *(int*)_item = self->var;
    return 2;
}

static char* to_string(void *_self)
{
    struct oc_object *self = _self;
    char *text;
    const char *example = "to_string_queue";
    text = malloc(strlen(example));
    strcpy(text,example);
    return text;
}

static const struct oc_object_vtable _vtable_object = { .to_string = to_string };
static const struct oc_queue_vtable _vtable = { .put = put, .get = get };

static void *ctor(void *_self, va_list *_args)
{
    struct oc_test_queue *self = OC_NEW_SUPER_CTOR(oc_queue, _self, _args);
    self->super.vtable = (struct oc_queue_vtable*)&_vtable;
    self->super.super.vtable = (struct oc_object_vtable*)&_vtable_object;
    self->var = 0;
    return self;
}

static void *dtor(void *_self)
{
    struct oc_test_queue *self = OC_NEW_SUPER_DTOR(oc_queue,_self);
    self->var = 0;
    return self;
}

static const struct oc_class _oc_test_queue = {sizeof(struct oc_test_queue), "oc_test_queue", ctor, dtor, NULL};
static const void * oc_test_queue = &_oc_test_queue;

/* ************************************************ */

static struct oc_test_queue *testObj;

static int test_start(void)
{
    testObj = NULL;
    testObj = oc_new(oc_test_queue, 4, 1);

    ASSERT(testObj != NULL);
    ASSERT(testObj->super.buffer_size == 4);
    ASSERT(testObj->super.item_size == 1);
    ASSERT(testObj->super.count == 0);

    return 0;
}

static int test_queue(void)
{
    char *text;
    int i;

    text = oc_object_to_string(testObj);
    ASSERT(strcmp(text, "to_string_queue") == 0);
    free(text);

    testObj->super.super.vtable = NULL;

    text = oc_object_to_string(testObj);
    ASSERT(strcmp(text, "oc_test_queue") == 0);
    free(text);

    ASSERT(oc_queue_is_empty(testObj) != 0);
    ASSERT(oc_queue_is_full(testObj) == 0);

    i = 1234;
    ASSERT(oc_queue_put(testObj,&i) == 1);
    ASSERT(testObj->var == 1234);

    i = 0;
    ASSERT(oc_queue_get(testObj,&i) == 2);
    ASSERT(i == 1234);

    testObj->super.count = 1;
    ASSERT(oc_queue_is_empty(testObj) == 0);
    ASSERT(oc_queue_is_full(testObj) == 0);

    testObj->super.count = 4;
    ASSERT(oc_queue_is_empty(testObj) == 0);
    ASSERT(oc_queue_is_full(testObj) != 0);

    testObj->super.vtable = NULL;

    ASSERT(oc_queue_put(testObj,&i) == 0);
    ASSERT(oc_queue_get(testObj,&i) == 0);
    
    return 0;
}

static int test_stop(void)
{
    ASSERT(testObj != NULL);
    oc_delete(testObj);
    ASSERT(testObj == NULL);

    return 0;
}

int test_oc_queue_all_tests(void)
{
    VERIFY(test_start);
    VERIFY(test_queue);
    VERIFY(test_stop);

    return 0;
}

