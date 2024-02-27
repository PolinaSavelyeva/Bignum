#include "bignum.h"
#ifndef HELPER_H
#define HELPER_H

bignum_t *init_bignum_mods(bool sign, unsigned int length);
bool is_equal(bignum_t *bignum_fst, bignum_t *bignum_snd);
void free_bignum(bignum_t *bignum);
bignum_t *init_bignum_digits(bool sign, unsigned int *digits, unsigned int length);

#endif