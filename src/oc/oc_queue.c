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

#include "oc_queue.h"

int oc_queue_put(void *_self, void *_item)
{
    struct oc_queue *self = _self;

    if (self->vtable == NULL) return 0;
    if (self->vtable->put == NULL) return 0;

    return self->vtable->put(self, _item);
}

int oc_queue_get(void *_self, void *_item)
{
    struct oc_queue *self = _self;

    if (self->vtable == NULL) return 0;
    if (self->vtable->get == NULL) return 0;

    return self->vtable->get(self, _item);
}

int oc_queue_is_empty(void *_self)
{
    struct oc_queue *self = _self;
    return (self->count == 0) ? 1 : 0;
}

int oc_queue_is_full(void *_self)
{
    struct oc_queue *self = _self;
    return (self->count == self->buffer_size) ? 1 : 0;
}

static void *ctor(void *_self, va_list *_args)
{
    struct oc_queue *self = _self;
    self->buffer_size = (int)va_arg(*_args, int);
    self->item_size = (int)va_arg(*_args, int);
    self->data = calloc(self->buffer_size, self->item_size);
    self->count = 0;
    return self;
}

static void *dtor(void *_self)
{
    struct oc_queue *self = _self;
    free(self->data);
    return self;
}

static const struct oc_class _oc_queue = {sizeof(struct oc_queue), "oc_queue", ctor, dtor, NULL};
const void * oc_queue = &_oc_queue;

