#include "bignum.h"
#include <stdbool.h>
#ifndef UTILS_H
#define UTILS_H

bignum_t *init_bignum_mods (sign_t sign, unsigned int length);

bool is_equal (bignum_t *bignum_fst, bignum_t *bignum_snd);

void free_bignum (bignum_t *bignum);
bignum_t *init_bignum_digits (sign_t sign, unsigned int *digits,
                              unsigned int length);

typedef bignum_t *(bin_op)(bignum_t *, bignum_t *);

bool test_op_res_eq_str (bin_op op, sign_t sign_fst, unsigned int length_fst,
                         sign_t sign_snd, unsigned int length_snd,
                         char *ans_str);

bool test_op_res_eq_int (bin_op op, int i_fst, int i_snd, int i_ans);

#endif