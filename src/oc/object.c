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

#include "object.h"

char* oc_object_to_string(void *_self)
{
    struct oc_object *self = _self;
    char *ret;
    const char *name;

    if (self->vtable != NULL) {
        if (self->vtable->to_string != NULL) {
            return self->vtable->to_string(self);
        }
    }

    name = ((struct oc_class*)self->class)->name;
    ret = malloc(strlen(name));
    strcpy(ret, name);
    return ret;
}

int oc_object_lock(void *_self)
{
    struct oc_object *self = _self;

    if (self->vtable != NULL) {
        if (self->vtable->lock != NULL) {
            return self->vtable->lock(self);
        }
    }

    if (self->locked != 0) return self->locked;
    self->locked = 1;
    return 0;
}

int oc_object_unlock(void *_self)
{
    struct oc_object *self = _self;
    
    if (self->vtable != NULL) {
        if (self->vtable->unlock != NULL) {
            return self->vtable->unlock(self);
        }
    }

    self->locked = 0;
    return 0;
}

int oc_object_is_locked(void *_self)
{
    struct oc_object *self = _self;
    
    if (self->vtable != NULL) {
        if (self->vtable->is_locked != NULL) {
            return self->vtable->is_locked(self);
        }
    }

    return self->locked;
}

static void *ctor(void *_self, va_list *_args)
{
    struct oc_object *self = _self;
    self->vtable = NULL;
    self->locked = 0;
    return self;
}

static void *dtor(void *_self)
{
    struct oc_object *self = _self;
    self->locked = 0;
    return self;
}

static const struct oc_class _oc_object = {sizeof(struct oc_object), "oc_object", ctor, dtor, NULL};
const void * oc_object = &_oc_object;

