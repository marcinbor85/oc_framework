# oc_framework
Simple Object-Oriented framework for C programming language.

## Main features
- classes
- single inheritance
- virtual table pointer
- overriding methods
- dynamic memory allocation
- abstract objects
- singleton pattern
- TDD tests
- build-in some useful classes

## The main assumptions of this library
- lightweight
- educational aspects
- code readability
- portability (embedded systems)
- easy to understand and to modification

## TODO:
- [ ] add generic list object
- [ ] add generic io stream object
- [ ] add some examples
- [ ] add source code documentation
- [ ] portability improvements

##Simple example:
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
    // should be out 4 5 6 7
    while (oc_queue_get(queue, &i) != 0) printf("%d ", i);

    // delete created queue object
    oc_delete(queue);

    return 0;
}
```

## Compile library (liboc.a) and run tests:

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

## Output example:

```sh
PASSED
Tests run: 24
```

