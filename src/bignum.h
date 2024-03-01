#include <stdbool.h>
#ifndef BIGNUM_H
#define BIGNUM_H

typedef enum
{
  NEG = -1,
  ZERO,
  POS
} sign_t;

typedef struct
{
  sign_t sign;
  unsigned int *digits;
  unsigned int length;
} bignum_t;

void free_bignum (bignum_t *bignum);

void *cut_zeros (bignum_t *bignum);

#endif /* BIGNUM_H */