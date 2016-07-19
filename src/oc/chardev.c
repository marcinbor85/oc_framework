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

#include "chardev.h"

int oc_chardev_put_char(void *_self, char *_char)
{
    struct oc_chardev *self = _self;
    int stat;

    if (self == NULL) return 0;
    if (_char == NULL) return 0;

    stat = oc_queue_put(self->output, _char);

    if (self->vtable == NULL) return stat;
    if (self->vtable->post_put == NULL) return stat;

    self->vtable->post_put(self);

    return stat;
}

int oc_chardev_get_char(void *_self, char *_char)
{
    struct oc_chardev *self = _self;
    int stat;

    if (self == NULL) return 0;
    if (_char == NULL) return 0;

    if (self->vtable != NULL) {
        if (self->vtable->pre_get != NULL) {
            self->vtable->pre_get(self);
        }
    }

    return oc_queue_get(self->input, _char);
}

int oc_chardev_pull_output(void *_self, char *_char)
{
    struct oc_chardev *self = _self;

    if (self == NULL) return 0;
    if (_char == NULL) return 0;

    return oc_queue_get(self->output, _char);
}

int oc_chardev_push_input(void *_self, char *_char)
{
    struct oc_chardev *self = _self;

    if (self == NULL) return 0;
    if (_char == NULL) return 0;

    return oc_queue_put(self->input, _char);
}

static void *ctor(void *_self, va_list *_args)
{
    struct oc_chardev *self = OC_NEW_SUPER_CTOR(oc_object, _self, _args);
    self->vtable = NULL;
    self->input = oc_new(oc_fifo, (int)va_arg(*_args, int), 1);
    self->output = oc_new(oc_fifo, (int)va_arg(*_args, int), 1);
    return self;
}

static void *dtor(void *_self)
{
    struct oc_chardev *self = OC_NEW_SUPER_DTOR(oc_object, _self);
    oc_delete(self->input);
    oc_delete(self->output);
    return self;
}

static const struct oc_class _oc_chardev = {sizeof(struct oc_chardev), "oc_chardev", ctor, dtor, NULL};
const void * oc_chardev = &_oc_chardev;

