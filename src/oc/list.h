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

#ifndef OC_LIST_H
#define OC_LIST_H

#include "object.h"

struct oc_list {
    OC_NEW_CLASS_EXTENDS(oc_object);
    void *first;
    void *last;
    int count;
};

struct oc_listitem {
    OC_NEW_CLASS_EXTENDS(oc_object);
    void *prev;
    void *next;
    void *list;
    void *data;
};

int oc_list_insert(void *_self, void *_item, const int _index);
int oc_list_add_first(void *_self, void *_item);
int oc_list_add_last(void *_self, void *_item);
int oc_list_remove(void *_self, void *_item);
int oc_list_is_empty(void *_self);
int oc_list_clear(void *_self);
int oc_list_get_count(void *_self);
int oc_list_has_item(void *_self, void *_item);
int oc_list_iterate(void *_self, int (*_callback)(void *_self, void *_item, void *_param), void *_param);

extern const void * oc_list;
extern const void * oc_listitem;

#endif /* OC_LIST_H */

