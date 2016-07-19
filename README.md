# oc_framework
Simple Object-Oriented framework for C programming language.
For documentation and more details see headers file of library source code.

### Main features
- classes
- single inheritance
- virtual table pointer
- overriding methods
- dynamic memory allocation
- abstract objects
- singleton pattern
- TDD tests
- build-in some useful classes
- examples

### Main goals
- lightweight
- educational aspects
- code readability
- portability (embedded systems)
- easy to understand and to modification

### TODO:
- [x] add generic list object
- [x] add generic chardev object
- [ ] add some extra examples
- [ ] add source code documentation
- [ ] portability improvements
- [ ] security improvements

# Examples
A few lines of source code means more than huge and fat documentation...

### Simple queue object example:
```c
#include <oc/fifo.h>
#include <stdio.h>

int main(void)
{
    // pointer to generic queue object
    struct oc_queue *queue;
    // auxiliary integer variable 
    int i;

    // create fifo queue object - fifo inherits from generic queue
    // there are space for 4 items, each of them has sizeof(int) size
    queue = oc_new(oc_fifo, 4, sizeof(int));

    // put 8 items to the queue
    // there should be buffer overrun, and some first items will be drop
    for (i = 0; i < 8; i++) oc_queue_put(queue, &i);

    // iterate over queue items, until queue will be empty
    // should be out: 4 5 6 7
    while (oc_queue_get(queue, &i) != 0) printf("%d ", i);

    // delete created queue object
    oc_delete(queue);

    return 0;
}
```

### Simple list object example:
```c
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
    oc_list_add_first(list, item1 = oc_new(oc_listitem, &i));
    oc_list_add_first(list, item2 = oc_new(oc_listitem, &j));

    // iterate over list, with passing parameter
    // should be out: [2] [1]
    oc_list_iterate(list, iterator, "[%d] ");

    // delete created list and list items object
    oc_delete(list);
    oc_delete(item1);
    oc_delete(item2);

    return 0;
}
```

### Compile library (liboc.a) and run tests:

```sh
mkdir build
mkdir config
mkdir m4
./autogen.sh
cd build
../configure
make
./src/tests/tests
```

### Output example:

```
PASSED
Tests run: 27
```

