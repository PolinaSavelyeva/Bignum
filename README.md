# Bignum Library

Bignum is a C library for arbitrary-precision arithmetic operations on large integers.

## Supported Features

- `abs_is_greater_or_eq`: Checks if the absolute value of one big number is greater than or equal to another.
- `add`: Performs addition of two big numbers.
- `diff`: Calculates the difference between two big numbers.
- `mult`: Multiplies two big numbers.
- `divide`: Divides one big number by another.
- `mod`: Calculates the modulus of one big number by another.
- `to_bignum`: Converts a string representation of a number to a big number.
- `to_str`: Converts a big number to its string representation.

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

## Requirements

- CMake (version 3.10 or higher)
- clang compiler supporting C11 standard
- valgrind
