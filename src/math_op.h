#include "bignum.h"
#ifndef MATH_OP_H
#define MATH_OP_H

static void abs_compare (bignum_t *fst, bignum_t *snd, bignum_t **big, bignum_t **small);

bignum_t *add (bignum_t *fst, bignum_t *snd);

bignum_t *diff (bignum_t *fst, bignum_t *snd);

bignum_t *mult (bignum_t *fst, bignum_t *snd);

bignum_t *divide (bignum_t *fst, bignum_t *snd);

bignum_t *mod (bignum_t *fst, bignum_t *snd);

#endif /* MATH_OP_H */