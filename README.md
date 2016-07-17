# oc_framework

Simple Object-Oriented framework for C programming language.

Main features:
- classes
- single inheritance
- virtual table pointer
- overriding methods
- dynamic memory allocation
- abstract objects
- singleton pattern
- TDD tests
- build-in some usefull classes

The main assumptions of this library:
- lightweight
- educational aspects
- code readability
- portability (embedded systems)
- easy to understand and to modification

Compile library (liboc.a) and run tests:

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

Output example:

```
PASSED
Tests run: 24
```



