#include "oc_new.h"

void* oc_new(const void *_class, ...)
{
    const struct OC_Class *class = _class;
    struct OC_Class **singleton = class->singleton;
    int init=0;
    void *p;
    
    if (singleton!=NULL) {
        if (*singleton==NULL) {
            p=calloc(1,class->size);
            *singleton=p;
            init=1;
        } else {
            p=*singleton; 
        }
    } else {
        p=calloc(1,class->size);
        init=1;
    }
    if (init!=0) {
        *(const struct OC_Class**)p=class;
        va_list arg;
        va_start(arg,_class);
        p=class->ctor(p,&arg);
        va_end(arg);
    }
    return p;
}

void oc_delete(void *_self)
{
    const struct OC_Class ** cp = _self;
    const struct OC_Class * class;
    struct OC_Class **singleton;
    
    if (_self!=NULL) {
        class=(*cp);
        _self=class->dtor(_self);
        if (_self!=NULL) {
            singleton=class->singleton;
            if (singleton!=NULL) {
                if (*singleton!=NULL) {
                    *singleton=NULL;
                }
            }
        }
        free(_self);
    }
}
