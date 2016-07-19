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

#ifndef OC_CHARDEV_H
#define OC_CHARDEV_H

#include "object.h"
#include "fifo.h"

struct oc_chardev_vtable {
    int (*put_char)(void *, char *);
    int (*get_char)(void *, char *);
};

struct oc_chardev {
    OC_NEW_CLASS_EXTENDS(oc_object);
    struct oc_queue *input;
    struct oc_queue *output;
};

int oc_chardev_put_char(void *_self, const char *_char);
int oc_chardev_get_char(void *_self, const char *_char);
int oc_chardev_push_out(void *_self);
int oc_chardev_pull_in(void *_self);

extern const void * oc_chardev;

#endif /* OC_CHARDEV_H */

