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

#include "list.h"

int oc_list_add_front(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_list_item *item = _item;

    if (oc_list_has_item(self,item) != 0) return 0;

    item->next = self->first;
    self->first = item;
    self->count++;
    return 1;
}

int oc_list_add_back(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_list_item *item = _item;
    struct oc_list_item *i = self->first;

    if (oc_list_has_item(self,item) != 0) return 0;

    if (self->first == NULL) {
        self->first = item;
        item->next = NULL;
    } else {
        while (i->next != NULL) i = i->next;
        i->next = item;
    }
    self->count++;
    return 1;
}

int oc_list_remove(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_list_item *item = _item;
    struct oc_list_item *i = self->first;
    struct oc_list_item *prev;

    if (self->first == NULL) return 0;
    
    while (i != _item) {
        prev = i;
        i = i->next;
        if (i == NULL) return 0;
    }

    if (i == self->first) {
        self->first = i->next;
    } else {
        prev->next = i->next;
    }

    i->next = NULL;

    
    self->count--;
    return 1;
}

int oc_list_is_empty(void *_self)
{
    struct oc_list *self = _self;
    return (self->first != NULL) ? 0 : 1;
}

int oc_list_get_count(void *_self)
{
    struct oc_list *self = _self;
    return self->count;
}

int oc_list_iterate(void *_self, int (*_callback)(void *_self, void *_item, void *_param), void *_param)
{
    struct oc_list *self = _self;
    struct oc_list_item *item;

    if (_callback == NULL) return 0;
    if (self->first == NULL) return 0;

    item = self->first;
    while (item != NULL) {
        if (_callback(self, item, _param) == 0) return 1;
        item = item->next;
    }

    return 1;
}

int oc_list_has_item(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_list_item *item = _item;
    struct oc_list_item *i = self->first;
    
    while (i != NULL) {
        if (i == _item) return 1;
        i = i->next;
    }
    return 0;
}

int oc_list_clear(void *_self)
{
    struct oc_list *self = _self;
    struct oc_list_item *i = self->first;
    struct oc_list_item *next;

    if (self->first == NULL) return 0;
    
    while (i != NULL) {
        next = i->next;
        i->next = NULL;
        i = next;
    }

    self->first = NULL;

    return 1;
}



static void *list_ctor(void *_self, va_list *_args)
{
    struct oc_list *self = OC_NEW_SUPER_CTOR(oc_object, _self, _args);
    self->first = NULL;
    self->count = 0;
    return self;
}

static void *list_dtor(void *_self)
{
    struct oc_list *self = OC_NEW_SUPER_DTOR(oc_object, _self);
    return self;
}

static const struct oc_class _oc_list = {sizeof(struct oc_list), "oc_list", list_ctor, list_dtor, NULL};
const void * oc_list = &_oc_list;

static void *item_ctor(void *_self, va_list *_args)
{
    struct oc_list_item *self = OC_NEW_SUPER_CTOR(oc_object, _self, _args);
    self->next = NULL;
    self->data = (void*)va_arg(*_args, void*);
    return self;
}

static void *item_dtor(void *_self)
{
    struct oc_list_item *self = OC_NEW_SUPER_DTOR(oc_object, _self);
    return self;
}

static const struct oc_class _oc_list_item = {sizeof(struct oc_list_item), "oc_list_item", item_ctor, item_dtor, NULL};
const void * oc_list_item = &_oc_list_item;

