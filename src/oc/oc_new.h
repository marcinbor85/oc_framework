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

