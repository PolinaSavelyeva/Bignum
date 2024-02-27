cmake_minimum_required(VERSION 3.10)
project(Bignum)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB 
    src/basic_op.c
    src/bignum.c
    src/math_op.c
    src/string_op.c
    tests/helper.c
)

add_library(bignum STATIC ${SOURCE_LIB})	
target_include_directories(bignum PUBLIC src)

add_executable(string_tests tests/string_tests.c)
target_link_libraries(string_tests bignum)

add_executable(math_tests tests/math_tests.c)
target_link_libraries(math_tests bignum)

enable_testing()

add_test(NAME StringTests COMMAND string_tests)
add_test(NAME MathTests COMMAND math_tests)
