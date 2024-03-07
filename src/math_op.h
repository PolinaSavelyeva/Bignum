#pragma once

#include "bignum.h"

bool bignum_cmp_abs(bignum_t *fst, bignum_t *snd);
bignum_t *bignum_add(bignum_t *fst, bignum_t *snd);
bignum_t *bignum_diff(bignum_t *fst, bignum_t *snd);
bignum_t *bignum_mult(bignum_t *fst, bignum_t *snd);
bignum_t *bignum_div(bignum_t *fst, bignum_t *snd);
bignum_t *bignum_mod(bignum_t *fst, bignum_t *snd);