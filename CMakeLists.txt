cmake_minimum_required(VERSION 3.10)
project(Bignum)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB 
    src/basic_op.c
    src/bignum.c
    src/math_op.c
    src/string_op.c
)

set(SOURCE_EXE src/main.c)

set(TESTS
    tests/main.c
    tests/string_tests.c
    src/string_op.c
)

include_directories(src)	

add_library(bignum STATIC ${SOURCE_LIB})	
add_executable(main ${SOURCE_EXE})
target_link_libraries(main bignum)	

add_executable(tests ${TESTS})
enable_testing()
add_test(NAME BignumTests COMMAND tests)