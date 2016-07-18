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

#include <oc/list.h>

#include <stdio.h>

static int iterator(void *_list, void *_item, void *_param)
{
    // pointer to passed parameter (in this case format string)
    const char *format = _param;
    // pointer to list item
    struct oc_listitem *item = _item;
    // pointer to list item data (in this case variable)
    int var = *(int*)item->data;

    // print data using passed parameters and list data
    printf(format, var);

    // continue iterate
    return 1;
}

int main(void)
{
    // pointer to generic list object
    struct oc_list *list;
    // pointers to generic list item objects
    struct oc_listitem *item1,*item2;
    // auxiliary integer variables 
    int i = 1;
    int j = 2;

    // create list object
    list = oc_new(oc_list);

    // add two items to the front of the list, with pointers to variables
    oc_list_add_front(list, item1 = oc_new(oc_listitem, &i));
    oc_list_add_front(list, item2 = oc_new(oc_listitem, &j));

    // iterate over list, with passing parameter
    // should be out: [2] [1]
    oc_list_iterate(list, iterator, "[%d] ");

    // delete created list and list items object
    oc_delete(list);
    oc_delete(item1);
    oc_delete(item2);

    return 0;
}

