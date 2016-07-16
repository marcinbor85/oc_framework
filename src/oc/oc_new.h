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

#ifndef OC_NEW_H
#define OC_NEW_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define OC_NEW_SUPER_CTOR(a,b,c) ((const struct OC_Class*)a)->ctor(b,c)
#define OC_NEW_SUPER_DTOR(a,b) ((const struct OC_Class*)a)->dtor(b)

#define OC_NEW_CLASS_EXTENDS(a) struct a super
#define OC_NEW_CLASS const void *class

struct OC_Class {
    int size;
    void* (*ctor)(void *_self, va_list *_args);
    void* (*dtor)(void *_self);
    void* singleton;
};

void* oc_new(const void *_class, ...);
void oc_delete(void *_self);

#endif /* OC_NEW_H */

