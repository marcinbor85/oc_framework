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

#include "tests.h"

#include <oc/list.h>

static struct oc_list *testList;
static struct oc_listitem *testItem1;
static struct oc_listitem *testItem2;
static struct oc_listitem *testItem3;

static int test_start(void)
{
    static int var1 = 10;
    static int var2 = 20;
    static int var3 = 50;

    testList = NULL;
    testList = oc_new(oc_list);

    testItem1 = oc_new(oc_listitem, &var1);
    testItem2 = oc_new(oc_listitem, &var2);
    testItem3 = oc_new(oc_listitem, &var3);

    ASSERT(testList != NULL);
    ASSERT(testList->first == NULL);
    ASSERT(testList->last == NULL);
    ASSERT(testList->count == 0);

    ASSERT(testItem1 != NULL);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem1->list == NULL);
    ASSERT(testItem1->data == &var1);

    ASSERT(testItem2 != NULL);
    ASSERT(testItem2->next == NULL);
    ASSERT(testItem2->prev == NULL);
    ASSERT(testItem2->list == NULL);
    ASSERT(testItem2->data == &var2);

    ASSERT(testItem3 != NULL);
    ASSERT(testItem3->next == NULL);
    ASSERT(testItem3->prev == NULL);
    ASSERT(testItem3->list == NULL);
    ASSERT(testItem3->data == &var3);

    return 0;
}

static int sum;
static int cntr;

static int test_list_iterate(void *_list, void *_item, void *_param)
{
    struct oc_list *list = _list;
    struct oc_listitem *item = _item;
    int param = *(int*)_param;
    int v;

    ASSERT((param == 100) || (param == 200));

    if (cntr == 0) v = 10;
    else if (cntr == 1) v = 50;
    else if (cntr == 2) v = 20;
    
    ASSERT(*(int*)(item->data) == v);

    ASSERT(list == testList);

    cntr++;
    sum+=v;

    if (param == 100) return 1;
    
    if (param == 200) {
        if (cntr==2) return 0;
        return 1;
    }

    return 0;
}

static int test_list(void)
{
    char *text;
    int i;
    int s;

    text = oc_object_to_string(testList);
    ASSERT(strcmp(text, "oc_list") == 0);
    free(text);

    text = oc_object_to_string(testItem1);
    ASSERT(strcmp(text, "oc_listitem") == 0);
    free(text);

    ASSERT(oc_list_is_empty(testList) != 0);
    ASSERT(oc_list_get_count(testList) == 0);

    ASSERT(oc_list_add_first(testList, testItem1) != 0);
    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 1);

    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem1);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem1->list == testList);

    ASSERT(oc_list_add_first(testList, testItem2) != 0);
    ASSERT(oc_list_get_count(testList) == 2);

    ASSERT(testList->first == testItem2);
    ASSERT(testList->last == testItem1);
    ASSERT(testItem2->next == testItem1);
    ASSERT(testItem2->prev == NULL);
    ASSERT(testItem2->list == testList);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == testItem2);

    ASSERT(oc_list_remove(testList, testItem3) == 0);

    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 2);

    ASSERT(oc_list_remove(testList, testItem2) != 0);
    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem1);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem1->list == testList);
    ASSERT(testItem2->next == NULL);
    ASSERT(testItem2->prev == NULL);
    ASSERT(testItem2->list == NULL);

    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 1);

    ASSERT(oc_list_remove(testList, testItem1) != 0);
    ASSERT(testList->first == NULL);
    ASSERT(testList->last == NULL);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem1->list == NULL);

    ASSERT(oc_list_is_empty(testList) != 0);
    ASSERT(oc_list_get_count(testList) == 0);

    ASSERT(oc_list_add_first(testList, testItem1) != 0);
    ASSERT(oc_list_get_count(testList) == 1);

    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem1);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem1->list == testList);

    ASSERT(oc_list_add_last(testList, testItem2) != 0);
    ASSERT(oc_list_get_count(testList) == 2);

    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem2);
    ASSERT(testItem1->next == testItem2);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem2->next == NULL);
    ASSERT(testItem2->prev == testItem1);
    ASSERT(testItem1->list == testList);
    ASSERT(testItem2->list == testList);

    ASSERT(oc_list_has_item(testList, testItem3) == 0);
    ASSERT(oc_list_has_item(testList, testItem2) != 0);
    ASSERT(oc_list_has_item(testList, testItem1) != 0);

    ASSERT(oc_list_add_last(testList, testItem3) != 0);
    ASSERT(oc_list_get_count(testList) == 3);
    ASSERT(testItem2->next == testItem3);
    ASSERT(testItem3->prev == testItem2);
    ASSERT(testItem3->next == NULL);
    ASSERT(testList->last == testItem3);
    ASSERT(oc_list_has_item(testList, testItem3) != 0);

    ASSERT(oc_list_add_last(testList, testItem3) == 0);
    ASSERT(oc_list_get_count(testList) == 3);

    ASSERT(oc_list_add_first(testList, testItem3) == 0);
    ASSERT(oc_list_get_count(testList) == 3);

    ASSERT(oc_list_remove(testList, testItem2) != 0);
    ASSERT(oc_list_get_count(testList) == 2);
    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem3);
    ASSERT(testItem1->next == testItem3);
    ASSERT(testItem3->prev == testItem1);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem3->next == NULL);

    ASSERT(oc_list_remove(testList, testItem2) == 0);
    ASSERT(oc_list_get_count(testList) == 2);

    ASSERT(oc_list_add_last(testList, testItem2) != 0);
    ASSERT(oc_list_get_count(testList) == 3);

    sum = 0;
    cntr = 0;
    i = 100;
    s = oc_list_iterate(testList, test_list_iterate, &i);
    ASSERT(sum == 80);
    ASSERT(cntr == 3);
    ASSERT(s == 1);

    sum = 0;
    cntr = 0;
    i = 200;
    s = oc_list_iterate(testList, test_list_iterate, &i);
    ASSERT(sum == 60);
    ASSERT(cntr == 2);
    ASSERT(s == 1);

    ASSERT(oc_list_clear(testList) != 0);
    ASSERT(testList->first == NULL);
    ASSERT(testList->last == NULL);
    ASSERT(testList->count == 0);

    ASSERT(testItem1->next == NULL);
    ASSERT(testItem2->next == NULL);
    ASSERT(testItem3->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem2->prev == NULL);
    ASSERT(testItem3->prev == NULL);
    ASSERT(testItem1->list == NULL);
    ASSERT(testItem2->list == NULL);
    ASSERT(testItem3->list == NULL);

    ASSERT(oc_list_clear(testList) == 0);

    ASSERT(oc_list_insert(testList, testItem1, 0) != 0);
    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 1);

    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem1);
    ASSERT(testItem1->next == NULL);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem1->list == testList);

    ASSERT(oc_list_insert(testList, testItem2, 1) != 0);
    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 2);

    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem2);
    ASSERT(testItem1->next == testItem2);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem2->next == NULL);
    ASSERT(testItem2->prev == testItem1);
    ASSERT(testItem2->list == testList);

    ASSERT(oc_list_insert(testList, testItem3, 1) != 0);
    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 3);

    ASSERT(testList->first == testItem1);
    ASSERT(testList->last == testItem2);
    ASSERT(testItem1->next == testItem3);
    ASSERT(testItem1->prev == NULL);
    ASSERT(testItem2->next == NULL);
    ASSERT(testItem2->prev == testItem3);
    ASSERT(testItem3->next == testItem2);
    ASSERT(testItem3->prev == testItem1);
    ASSERT(testItem3->list == testList);

    ASSERT(oc_list_insert(testList, testItem3, 0) == 0);
    ASSERT(oc_list_is_empty(testList) == 0);
    ASSERT(oc_list_get_count(testList) == 3);

    return 0;
}

static int test_stop(void)
{
    ASSERT(testList != NULL);
    oc_delete(testList);
    ASSERT(testList == NULL);

    ASSERT(testItem1 != NULL);
    oc_delete(testItem1);
    ASSERT(testItem1 == NULL);

    ASSERT(testItem2 != NULL);
    oc_delete(testItem2);
    ASSERT(testItem2 == NULL);

    ASSERT(testItem3 != NULL);
    oc_delete(testItem3);
    ASSERT(testItem3 == NULL);

    return 0;
}

int test_oc_list_all_tests(void)
{
    VERIFY(test_start);
    VERIFY(test_list);
    VERIFY(test_stop);

    return 0;
}

