cmake_minimum_required(VERSION 3.10)
project(Bignum)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB 
    src/bignum.c
    src/math_op.c
    src/string_op.c
    tests/utils.c
)

add_library(bignum STATIC ${SOURCE_LIB})	
target_include_directories(bignum PUBLIC src)
target_link_libraries(bignum m)

# Add compiler flags
target_compile_options(bignum PRIVATE -Wall -g)

# Executable tests
add_executable(string_tests tests/string_tests.c)
target_link_libraries(string_tests bignum)

add_executable(math_tests tests/math_tests.c)
target_link_libraries(math_tests bignum)

add_executable(alg_tests tests/alg_tests.c)
target_link_libraries(alg_tests bignum)

enable_testing()

add_test(NAME StringTests COMMAND string_tests)
add_test(NAME MathTests COMMAND math_tests)
add_test(NAME AlgTests COMMAND alg_tests)

# Group files to format
file(GLOB_RECURSE ALL_SOURCE_FILES *.c *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND SOURCE_FILE PROJECT_TRDPARTY_DIR PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()

# Formatter
add_custom_target (format
     COMMAND clang-format -style=Google -i ${ALL_SOURCE_FILES})

# Memcheck
add_custom_target(memcheck 
    COMMAND valgrind --leak-check=full ./alg_tests)