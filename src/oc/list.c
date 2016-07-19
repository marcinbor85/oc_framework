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

int oc_list_insert(void *_self, void *_item, const int _index)
{
    struct oc_list *self = _self;
    struct oc_listitem *item = _item;
    struct oc_listitem *left;
    struct oc_listitem *right;
    int i;

    if (self == NULL) return 0;
    if (item == NULL) return 0;
    if (item->list == self) return 0;

    if (_index == 0) return oc_list_add_first(self, item);
    if (_index >= self->count) return oc_list_add_last(self, item);

    i = 0;
    right = self->first;
    while (i++ != _index) right = right->next;
    left = right->prev;

    left->next = item;
    item->prev = left;
    right->prev = item;
    item->next = right;

    item->list = self;

    self->count++;
    return 1;
}

int oc_list_add_first(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_listitem *item = _item;

    if (self == NULL) return 0;
    if (item == NULL) return 0;
    if (item->list == self) return 0;

    if (item->list != NULL) oc_list_remove(item->list, item);

    if (self->first != NULL) ((struct oc_listitem *)(self->first))->prev = item;

    item->next = self->first;
    item->prev = NULL;
    item->list = self;
    self->first = item;

    if (item->next == NULL) self->last = item;

    self->count++;
    return 1;
}

int oc_list_add_last(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_listitem *item = _item;

    if (self == NULL) return 0;
    if (item == NULL) return 0;
    if (item->list == self) return 0;

    if (item->list != NULL) oc_list_remove(item->list, item);

    if (self->last != NULL) ((struct oc_listitem *)(self->last))->next = item;

    item->prev = self->last;
    item->next = NULL;
    item->list = self;
    self->last = item;

    if (item->prev == NULL) self->first = item;

    self->count++;
    return 1;
}

int oc_list_remove(void *_self, void *_item)
{
    struct oc_list *self = _self;
    struct oc_listitem *item = _item;

    if (self == NULL) return 0;
    if (item == NULL) return 0;
    if (item->list != self) return 0;
    if (self->count == 0) return 0;

    if (self->first == item) self->first = item->next;
    if (self->last == item) self->last = item->prev;

    if (item->next != NULL) ((struct oc_listitem *)(item->next))->prev = item->prev;
    if (item->prev != NULL) ((struct oc_listitem *)(item->prev))->next = item->next;

    item->prev = NULL;
    item->next = NULL;
    item->list = NULL;

    self->count--;
    return 1;
}

int oc_list_is_empty(void *_self)
{
    struct oc_list *self = _self;
    if (self == NULL) return 1;
    return (self->count == 0) ? 1 : 0;
}

int oc_list_get_count(void *_self)
{
    struct oc_list *self = _self;
    if (self == NULL) return 0;
    return self->count;
}

int oc_list_iterate(void *_self, int (*_callback)(void *_self, void *_item, void *_param), void *_param)
{
    struct oc_list *self = _self;
    struct oc_listitem *item;

    if (self == NULL) return 0;
    if (_callback == NULL) return 0;
    if (self->count == 0) return 0;

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
    struct oc_listitem *item = _item;
    if (self == NULL) return 0;
    if (item == NULL) return 1;
    return (item->list == self) ? 1 : 0;
}

int oc_list_clear(void *_self)
{
    struct oc_list *self = _self;
    struct oc_listitem *item;
    struct oc_listitem *next;

    if (self == NULL) return 0;
    if (self->count == 0) return 0;
    
    item = self->first;
    while (item != NULL) {
        next = item->next;
        item->next = NULL;
        item->prev = NULL;
        item->list = NULL;
        item = next;
    }

    self->first = NULL;
    self->last = NULL;
    self->count = 0;

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
    struct oc_listitem *self = OC_NEW_SUPER_CTOR(oc_object, _self, _args);
    self->next = NULL;
    self->data = (void*)va_arg(*_args, void*);
    return self;
}

static void *item_dtor(void *_self)
{
    struct oc_listitem *self = OC_NEW_SUPER_DTOR(oc_object, _self);
    return self;
}

static const struct oc_class _oc_listitem = {sizeof(struct oc_listitem), "oc_listitem", item_ctor, item_dtor, NULL};
const void * oc_listitem = &_oc_listitem;

