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

