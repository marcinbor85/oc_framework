#include "tests.h"

#include "oc/oc_new.h"

/* ************************************************ */

struct OC_AbstractTestObject_VTable {
    int (*set)(void *, void *);
    int (*get)(void *, void *);
    int (*change)(void *);
};

struct OC_AbstractTestObject {
    OC_NEW_CLASS;
    struct OC_AbstractTestObject_VTable *vTable;
};

static int method_set(void *_self, void *_i) {
    struct OC_AbstractTestObject *self=_self;
    if (self->vTable == NULL) return -1;
    if (self->vTable->set == NULL) return -1;
    return self->vTable->set(_self, _i);
}

static int method_get(void *_self, void *_i) {
    struct OC_AbstractTestObject *self=_self;
    if (self->vTable == NULL) return -1;
    if (self->vTable->get == NULL) return -1;
    return self->vTable->get(_self, _i);
}

static int method_change(void *_self) {
    struct OC_AbstractTestObject *self=_self;
    if (self->vTable == NULL) return -1;
    if (self->vTable->change == NULL) return -1;
    return self->vTable->change(_self);
}

static void *OC_AbstractTestObject_ctor(void *_self, va_list *_args) {
    struct OC_AbstractTestObject *self = _self;
    return self;
}

static void *OC_AbstractTestObject_dtor(void *_self) {
    struct OC_AbstractTestObject *self = _self;
    return self;
}

static const struct OC_Class _OC_AbstractTestObject = {sizeof(struct OC_AbstractTestObject), OC_AbstractTestObject_ctor, OC_AbstractTestObject_dtor, NULL};
static const void * OC_AbstractTestObject = &_OC_AbstractTestObject;

/* ************************************************ */

struct OC_ExtendedTestObject {
    OC_NEW_CLASS_EXTENDS(OC_AbstractTestObject);
    int var;
};

static int _set(void *_self, void *_i) {
    struct OC_ExtendedTestObject *self = _self;
    self->var = *(int*)_i;
    return 0;
}

static int _get(void *_self, void *_i) {
    struct OC_ExtendedTestObject *self = _self;
    *(int*)_i = self->var;
    return 0;
}

static const struct OC_AbstractTestObject_VTable _vTable = { .set = _set, .get = _get };

static void *OC_ExtendedTestObject_ctor(void *_self, va_list *_args) {
    struct OC_ExtendedTestObject *self = OC_NEW_SUPER_CTOR(OC_AbstractTestObject, _self, _args);
    self->super.vTable = (struct OC_AbstractTestObject_VTable*)&_vTable;
    self->var = (int)va_arg(*_args, int);
    return self;
}

static void *OC_ExtendedTestObject_dtor(void *_self) {
    struct OC_ExtendedTestObject *self = OC_NEW_SUPER_DTOR(OC_AbstractTestObject,_self);
    self->var = 0;
    return self;
}

static const struct OC_Class _OC_ExtendedTestObject = {sizeof(struct OC_ExtendedTestObject), OC_ExtendedTestObject_ctor, OC_ExtendedTestObject_dtor, NULL};
static const void * OC_ExtendedTestObject = &_OC_ExtendedTestObject;

/* ************************************************ */

static struct OC_ExtendedTestObject *testObj;

static int test_ctor(void)
{
    int var = 1234;

    testObj=NULL;
    testObj=oc_new(OC_ExtendedTestObject, var);

    ASSERT(testObj != NULL);
    ASSERT(malloc_usable_size(testObj) >= sizeof(struct OC_ExtendedTestObject));
    ASSERT(testObj->super.class == OC_ExtendedTestObject);
    ASSERT(testObj->super.vTable == &_vTable);
    ASSERT(testObj->var == var);

    return 0;
}

static int test_method(void)
{
    int var = 9999;
    int ret;
    int s;

    s = method_set(testObj,&var);
    ASSERT(testObj->var == var);
    ASSERT(s == 0);

    s = method_get(testObj,&ret);
    ASSERT(testObj->var == ret);
    ASSERT(testObj->var == var);
    ASSERT(s == 0);

    s = method_change(testObj);
    ASSERT(s != 0);

    return 0;
}

static int test_dtor(void)
{
    oc_delete(testObj);

    return 0;
}

int test_oc_new_vtable_all_tests(void)
{
    VERIFY(test_ctor);
    VERIFY(test_method);
    VERIFY(test_dtor);

    return 0;
}

