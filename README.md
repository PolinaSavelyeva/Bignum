# Bignum

Bignum is a C library for arbitrary-precision arithmetic operations on large integers.

## Main Features

- `bignum_add`: Performs addition of two big ints.
- `bignum_diff`: Calculates the difference between two big ints.
- `bignum_mult`: Multiplies two big ints.
- `bignum_div`: Divides one big int by another.
- `bignum_mod`: Calculates the modulus of one big int by another.
- `str_to_bignum`: Converts a string representation of an int to a big int.
- `bignum_to_str`: Converts a big int to its string representation.

## Building

To build the Bignum library, follow these steps:

1. Clone the repository:

    ```
    git clone https://github.com/PolinaSavelyeva/Bignum.git
    ```

2. Navigate to the Bignum directory:

    ```
    cd Bignum
    ```

3. Build the library using CMake:

    ```
    cmake .
    make
    ```

## Build Requirements

- CMake (version 3.10 or higher)
- clang compiler supporting C11 standard
- valgrind
