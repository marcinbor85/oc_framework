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

#include <oc/lifo.h>

static struct oc_lifo *testObj;

static int test_start(void)
{
    testObj = NULL;
    testObj = oc_new(oc_lifo, 4, 1);

    ASSERT(testObj != NULL);
    ASSERT(testObj->super.buffer_size == 4);
    ASSERT(testObj->super.item_size == 1);
    ASSERT(testObj->super.count == 0);

    return 0;
}

static int test_queue(void)
{
    char *text;
    char c;
    int s;

    text = oc_object_to_string(testObj);
    ASSERT(strcmp(text, "oc_lifo") == 0);
    free(text);

    ASSERT(oc_queue_is_empty(testObj) != 0);
    ASSERT(oc_queue_is_full(testObj) == 0);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 0);
    ASSERT(c == 0);

    c = 10;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);
    
    ASSERT(oc_queue_is_empty(testObj) == 0);
    ASSERT(oc_queue_is_full(testObj) == 0);

    c = 20;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);

    c = 30;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 30);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 20);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 10);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 0);
    ASSERT(c == 0);

    ASSERT(oc_queue_is_empty(testObj) != 0);
    ASSERT(oc_queue_is_full(testObj) == 0);

    c = 10;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);

    c = 20;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);

    c = 30;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);

    c = 40;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 1);

    ASSERT(oc_queue_is_empty(testObj) == 0);
    ASSERT(oc_queue_is_full(testObj) != 0);

    c = 50;
    s = oc_queue_put(testObj, &c);
    ASSERT(s == 0);

    ASSERT(oc_queue_is_empty(testObj) == 0);
    ASSERT(oc_queue_is_full(testObj) != 0);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 50);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 40);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 30);

    c = 0;
    s = oc_queue_get(testObj, &c);
    ASSERT(s == 1);
    ASSERT(c == 20);

    ASSERT(oc_queue_is_empty(testObj) != 0);
    ASSERT(oc_queue_is_full(testObj) == 0);
    
    return 0;
}

static int test_stop(void)
{
    ASSERT(testObj != NULL);
    oc_delete(testObj);
    ASSERT(testObj == NULL);

    return 0;
}

int test_oc_lifo_all_tests(void)
{
    VERIFY(test_start);
    VERIFY(test_queue);
    VERIFY(test_stop);

    return 0;
}

