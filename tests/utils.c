#include "utils.h"

#include <stdlib.h>
#include <string.h>

#include "bignum.h"
#include "string_op.h"

bignum_t *
init_bignum_mods (sign_t sign, unsigned int length)
{
  bignum_t *bignum = malloc (sizeof (bignum_t));

  bignum->digits = malloc (length * sizeof (unsigned int));
  bignum->sign = sign;
  bignum->length = length;

  for (unsigned int i = 0; i < length; i++)
    bignum->digits[length - i - 1] = (i + 1) % 10;

  return bignum;
}

bignum_t *
init_bignum_digits (sign_t sign, unsigned int *digits, unsigned int length)
{
  bignum_t *bignum = malloc (sizeof (bignum_t));

  bignum->sign = sign;
  bignum->length = length;
  bignum->digits = digits;

  return bignum;
}

bool
is_equal (bignum_t *bignum_fst, bignum_t *bignum_snd)
{
  return (bignum_fst->sign == bignum_snd->sign
          && bignum_fst->length == bignum_snd->length
          && !memcmp (bignum_fst->digits, bignum_snd->digits,
                      bignum_fst->length * sizeof (unsigned int)));
}

bool
test_op_res_eq_str (bin_op op, sign_t sign_fst, unsigned int length_fst,
                    sign_t sign_snd, unsigned int length_snd, char *ans_str)
{
  bignum_t *fst = init_bignum_mods (sign_fst, length_fst);
  bignum_t *snd = init_bignum_mods (sign_snd, length_snd);
  bignum_t *expect = to_bignum (ans_str);
  bignum_t *actual = op (fst, snd);

  bool res = is_equal (actual, expect);

  free_bignum (fst);
  free_bignum (snd);
  free_bignum (expect);
  free_bignum (actual);

  return res;
}

bool
test_op_res_eq_int (bin_op op, int i_fst, int i_snd, int i_ans)
{
  bignum_t *fst = init_bignum_from_int (i_fst);
  bignum_t *snd = init_bignum_from_int (i_snd);
  bignum_t *expect = init_bignum_from_int (i_ans);
  bignum_t *actual = op (fst, snd);

  bool res = is_equal (actual, expect);

  free_bignum (fst);
  free_bignum (snd);
  free_bignum (expect);
  free_bignum (actual);

  return res;
}