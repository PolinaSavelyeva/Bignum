#include <stdbool.h>
#ifndef BIGNUM_H
#define BIGNUM_H

typedef enum { NEG = -1, ZERO, POS } sign_t;

typedef struct {
  sign_t sign;
  unsigned int *digits;
  unsigned int length;
} bignum_t;

void free_bignum(bignum_t *bignum);

void *cut_zeros(bignum_t *bignum);

bignum_t *init_bignum(sign_t sign, unsigned int *digits, unsigned int length);

bignum_t *init_bignum_from_int(int num);

bool is_equal(bignum_t *fst, bignum_t *snd);

#endif /* BIGNUM_H */