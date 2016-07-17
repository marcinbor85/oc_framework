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

#include "oc_new.h"

void* oc_new(const void *_class, ...)
{
    const struct oc_class *class = _class;
    struct oc_class **singleton = class->singleton;
    int init=0;
    void *p;
    
    if (singleton != NULL) {
        if (*singleton == NULL) {
            p = calloc(1, class->size);
            *singleton = p;
            init = 1;
        } else {
            p = *singleton; 
        }
    } else {
        p = calloc(1, class->size);
        init = 1;
    }
    if (init != 0) {
        *(const struct oc_class**)p = class;
        va_list arg;
        va_start(arg, _class);
        p = class->ctor(p, &arg);
        va_end(arg);
    }
    return p;
}

void _oc_delete(void *_self)
{
    const struct oc_class ** cp = _self;
    const struct oc_class * class;
    struct oc_class **singleton;
    
    if (_self != NULL) {
        class = (*cp);
        _self = class->dtor(_self);
        if (_self != NULL) {
            singleton = class->singleton;
            if (singleton != NULL) {
                if (*singleton != NULL) {
                    *singleton = NULL;
                }
            }
        }
        free(_self);
    }
}
