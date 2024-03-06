#pragma once

#include <stdbool.h>

typedef enum { NEG = -1, ZERO, POS } sign_t;

typedef struct {
  sign_t sign;
  unsigned int *digits;
  unsigned int length;
} bignum_t;

void free_bignum(bignum_t *bignum);
void normalize_bignum(bignum_t *bignum);
bignum_t *init_bignum(sign_t sign, unsigned int length);
bignum_t *init_bignum_from_int(int num);
bignum_t *init_bignum_with_digits(sign_t sign, unsigned int *digits,
                                  unsigned int length);
bool bignums_is_equal(bignum_t *fst, bignum_t *snd);