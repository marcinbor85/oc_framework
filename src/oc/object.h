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

#ifndef OC_OBJECT_H
#define OC_OBJECT_H

#include "new.h"

struct oc_object_vtable {
    char* (*to_string)(void *_self);
    int (*lock)(void *_self);
    int (*unlock)(void *_self);
    int (*is_locked)(void *_self);
};

struct oc_object {
    OC_NEW_CLASS;
    struct oc_object_vtable *vtable;
    int locked;
};

char* oc_object_to_string(void *_self);
int oc_object_lock(void *_self);
int oc_object_unlock(void *_self);
int oc_object_is_locked(void *_self);

extern const void * oc_object;

#endif /* OC_OBJECT_H */

