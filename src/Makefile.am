noinst_LIBRARIES = liboc.a
liboc_a_SOURCES = oc/oc_new.c oc/oc_new.h oc/oc_object.c oc/oc_object.h oc/oc_queue.c oc/oc_queue.h
bin_PROGRAMS = tests
tests_SOURCES = tests.c tests.h test_oc_new.c test_oc_new_singleton.c test_oc_new_inherit.c test_oc_new_vtable.c test_oc_object.c test_oc_queue.c
tests_LDADD = liboc.a
