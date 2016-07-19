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

int oc_chardev_put_char(void *_self, const char *_char)
{
    struct oc_chardev *self = _self;
    if (self == NULL) return 0;
    return 0;
}

int oc_chardev_get_char(void *_self, const char *_char)
{
    struct oc_chardev *self = _self;
    if (self == NULL) return 0;
    return 0;
}

int oc_chardev_push_out(void *_self)
{
    struct oc_chardev *self = _self;
    if (self == NULL) return 0;
    return 0;
}

int oc_chardev_pull_in(void *_self)
{
    struct oc_chardev *self = _self;
    if (self == NULL) return 0;
    return 0;
}

static void *ctor(void *_self, va_list *_args)
{
    struct oc_chardev *self = OC_NEW_SUPER_CTOR(oc_object, _self, _args);
    return self;
}

static void *dtor(void *_self)
{
    struct oc_chardev *self = OC_NEW_SUPER_DTOR(oc_object, _self);
    return self;
}

static const struct oc_class _oc_chardev = {sizeof(struct oc_chardev), "oc_chardev", ctor, dtor, NULL};
const void * oc_chardev = &_oc_chardev;

