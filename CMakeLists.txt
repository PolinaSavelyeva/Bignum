cmake_minimum_required(VERSION 3.10)
project(Bignum)

set(CMAKE_C_STANDARD 11)

set(SOURCES 
    src/basic_op.c
    src/bignum.c
    src/math_op.c
    src/string_op.c
    src/main.c
)

set(TESTS
    tests/main.c
    tests/string_op.c
)

include_directories(src)

add_executable(bignum ${SOURCES})

add_executable(tests ${TESTS})

enable_testing()
add_test(NAME BignumTests COMMAND tests)

