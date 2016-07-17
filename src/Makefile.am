noinst_LIBRARIES = liboc.a
liboc_a_SOURCES = oc/oc_new.c oc/oc_new.h oc/oc_object.c oc/oc_object.h oc/oc_queue.c oc/oc_queue.h oc/oc_fifo.c oc/oc_fifo.h oc/oc_lifo.c oc/oc_lifo.h
bin_PROGRAMS = tests
tests_SOURCES = tests.c tests.h test_oc_new.c test_oc_new_singleton.c test_oc_new_inherit.c test_oc_new_vtable.c test_oc_object.c test_oc_queue.c test_oc_fifo.c test_oc_lifo.c
tests_LDADD = liboc.a
