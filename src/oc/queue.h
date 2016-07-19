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

#ifndef OC_QUEUE_H
#define OC_QUEUE_H

#include "object.h"

struct oc_queue_vtable {
    int (*put)(void *_self, void *_item);
    int (*get)(void *_self, void *_item);
};

struct oc_queue {
    OC_NEW_CLASS_EXTENDS(oc_object);
    struct oc_queue_vtable *vtable;
    void *data;
    int buffer_size;
    int item_size;
    int count;
};

int oc_queue_put(void *_self, void *_item);
int oc_queue_get(void *_self, void *_item);
int oc_queue_is_empty(void *_self);
int oc_queue_is_full(void *_self);
int oc_queue_get_count(void *_self);

extern const void * oc_queue;

#endif /* OC_QUEUE_H */

