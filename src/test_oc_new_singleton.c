#include "tests.h"

#include "oc/oc_new.h"

/* ************************************************ */

static struct OC_TestObject *_singleton;

struct OC_TestObject {
    OC_NEW_CLASS;
    int var;
};

static void *ctor(void *_self, va_list *_args) {
    struct OC_TestObject *self = _self;
    self->var = (int)va_arg(*_args, int);
    return self;
}

static void *dtor(void *_self) {
    struct OC_TestObject *self = _self;
    self->var = 0;
    return self;
}

static const struct OC_Class _OC_TestObject = {sizeof(struct OC_TestObject), ctor, dtor, &_singleton};
static const void * OC_TestObject = &_OC_TestObject;

/* ************************************************ */

static struct OC_TestObject *testObj;
static struct OC_TestObject *testObj2;

static int test_ctor(void)
{
    int var = 1234;
    int var2 = 5678;

    testObj = NULL;
    testObj = oc_new(OC_TestObject, var);

    ASSERT(testObj != NULL);
    ASSERT(malloc_usable_size(testObj) >= sizeof(struct OC_TestObject));
    ASSERT(testObj->class == &_OC_TestObject);
    ASSERT(testObj->var == var);

    testObj2 = NULL;
    testObj2 = oc_new(OC_TestObject, var2);

    ASSERT(testObj2 == testObj);
    ASSERT(testObj2->var == testObj->var);
    ASSERT(testObj2->var == var);

    return 0;
}

static int test_dtor(void)
{
    oc_delete(testObj);

    return 0;
}

int test_oc_new_singleton_all_tests(void)
{
    VERIFY(test_ctor);
    VERIFY(test_dtor);

    return 0;
}

