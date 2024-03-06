#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include "bignum.h"
#include "math_op.h"
#include "string_op.h"

bignum_t *init_bignum_mods(sign_t sign, unsigned int length) {
  bignum_t *bignum = init_bignum(sign, length);

  for (unsigned int i = 0; i < length; i++)
    bignum->digits[length - i - 1] = (i + 1) % 10;

  return bignum;
}

bool test_op_res_eq_str(bin_op op, sign_t sign_fst, unsigned int length_fst,
                        sign_t sign_snd, unsigned int length_snd,
                        char *ans_str) {
  bignum_t *fst = init_bignum_mods(sign_fst, length_fst);
  bignum_t *snd = init_bignum_mods(sign_snd, length_snd);
  bignum_t *expect = to_bignum(ans_str);
  bignum_t *actual = op(fst, snd);

  bool res = bignums_is_equal(actual, expect);

  free_bignum(fst);
  free_bignum(snd);
  free_bignum(expect);
  free_bignum(actual);

  return res;
}

bool test_op_res_eq_int(bin_op op, int i_fst, int i_snd, int i_ans) {
  bignum_t *fst = init_bignum_from_int(i_fst);
  bignum_t *snd = init_bignum_from_int(i_snd);
  bignum_t *expect = init_bignum_from_int(i_ans);
  bignum_t *actual = op(fst, snd);

  bool res = bignums_is_equal(actual, expect);

  free_bignum(fst);
  free_bignum(snd);
  free_bignum(expect);
  free_bignum(actual);

  return res;
}

static bignum_t *copy(bignum_t *src) {
  bignum_t *dest = init_bignum(src->sign * src->sign, src->length);
  memcpy(dest->digits, src->digits, dest->length * sizeof(unsigned int));

  return dest;
}

bignum_t *euclidean_alg(bignum_t *fst, bignum_t *snd) {
  if (!abs_is_greater_or_eq(fst, snd)) return euclidean_alg(snd, fst);

  bignum_t *tmp_fst = copy(fst);
  bignum_t *tmp_snd = copy(snd);

  bignum_t *mod_res;
  do {
    mod_res = bignum_mod(tmp_fst, tmp_snd);
    free_bignum(tmp_fst);
    tmp_fst = tmp_snd;
    tmp_snd = mod_res;
  } while (mod_res->sign);

  free_bignum(tmp_snd);

  return tmp_fst;
}