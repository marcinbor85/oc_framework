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

#include "lifo.h"

static int put(void *_self, void *_item)
{
    struct oc_lifo *self = _self;
    
    memcpy((char*)&(((char*)self->super.data)[self->last*self->super.item_size]), (char*)_item, self->super.item_size);
    self->last++;
    if (self->last >= self->super.buffer_size) self->last=0;
    self->super.count++;
    if (self->super.count > self->super.buffer_size) {
        self->super.count = self->super.buffer_size;
        return 0;
    }

    return 1;
}

static int get(void *_self, void *_item)
{
    struct oc_lifo *self = _self;
    
    if (self->super.count == 0) return 0;
    if (self->last == 0) self->last = self->super.buffer_size-1;
    else self->last--;
    self->super.count--;
    memcpy((char*)_item, (char*)&(((char*)self->super.data)[self->last*self->super.item_size]),self->super.item_size);

    return 1;
}

static const struct oc_queue_vtable _vtable = { .put = put, .get = get };

static void *ctor(void *_self, va_list *_args)
{
    struct oc_lifo *self = OC_NEW_SUPER_CTOR(oc_queue, _self, _args);
    self->super.vtable = (struct oc_queue_vtable*)&_vtable;
    self->last = 0;
    return self;
}

static void *dtor(void *_self)
{
    struct oc_lifo *self = OC_NEW_SUPER_DTOR(oc_queue, _self);
    return self;
}

static const struct oc_class _oc_lifo = {sizeof(struct oc_lifo), "oc_lifo", ctor, dtor, NULL};
const void * oc_lifo = &_oc_lifo;

