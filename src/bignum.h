#include <stdbool.h>
#ifndef BIGNUM_H
#define BIGNUM_H

typedef struct
{
    bool sign;
    unsigned int *digits;
    unsigned int length;
} bignum_t;

#endif /* BIGNUM_H */