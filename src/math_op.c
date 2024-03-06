#include "math_op.h"

#include <stdlib.h>
#include <string.h>

bool abs_is_greater_or_eq(bignum_t *fst, bignum_t *snd) {
  if (fst->length == snd->length) {
    for (unsigned int i = 0; i < fst->length; i++) {
      if (fst->digits[fst->length - 1 - i] == snd->digits[fst->length - 1 - i])
        continue;
      return (fst->digits[fst->length - 1 - i] >
              snd->digits[fst->length - 1 - i]);
    }
  } else if (fst->length < snd->length)
    return 0;

  return 1;
}

static int math_div_ten(int num) {
  int div = num / 10;
  return num < 0 ? div - 1 : div;
}

static int math_mod_ten(int num) {
  int mod = num % 10;
  return mod < 0 ? mod + 10 : mod;
}

bignum_t *add(bignum_t *fst, bignum_t *snd) {
  if (!abs_is_greater_or_eq(fst, snd)) return add(snd, fst);

  bignum_t *res =
      init_bignum(fst->sign, calloc(fst->length + 1, sizeof(unsigned int)),
                  fst->length + 1);

  int carry = 0;

  for (unsigned int i = 0; i < fst->length; i++) {
    int cur_sum = fst->digits[i] + carry;

    if (i < snd->length) cur_sum += fst->sign * snd->sign * snd->digits[i];

    res->digits[i] = math_mod_ten(cur_sum);
    carry = math_div_ten(cur_sum);
  }

  res->digits[res->length - 1] = res->sign * carry;
  if (!cut_zeros(res)) return NULL;

  return res;
}

bignum_t *diff(bignum_t *fst, bignum_t *snd) {
  bignum_t *op_sign_snd =
      init_bignum(snd->sign * NEG, snd->digits, snd->length);
  bignum_t *ans = add(fst, op_sign_snd);
  free(op_sign_snd);

  return ans;
}

bignum_t *mult(bignum_t *fst, bignum_t *snd) {
  bignum_t *res =
      init_bignum(fst->sign * snd->sign,
                  calloc(fst->length + snd->length, sizeof(unsigned int)),
                  fst->length + snd->length);
  for (unsigned int i = 0; i < fst->length; i++) {
    unsigned int carry = 0;
    for (unsigned int j = 0; j < snd->length; j++) {
      unsigned int sum =
          fst->digits[i] * snd->digits[j] + res->digits[i + j] + carry;
      res->digits[i + j] = sum % 10;
      carry = sum / 10;
    }
    res->digits[i + snd->length] = carry;
  }

  if (!cut_zeros(res)) return NULL;

  return res;
}

static int find_cur_quotient(bignum_t *cur_dividend, bignum_t *snd) {
  int i_quotient = 0;
  bignum_t *tmp_mult, *bignum_quotient;

  for (; i_quotient < 10; i_quotient++) {
    bignum_quotient = init_bignum_from_int(i_quotient);
    tmp_mult = mult(snd, bignum_quotient);

    bool is_break = !abs_is_greater_or_eq(cur_dividend, tmp_mult);

    free_bignum(tmp_mult);
    free_bignum(bignum_quotient);

    if (is_break) break;
  }
  return i_quotient - 1;
}

bignum_t *divide(bignum_t *fst, bignum_t *snd) {
  if (!snd->length && !snd->sign && !snd->digits) return NULL;

  bignum_t *res =
      init_bignum(fst->sign * snd->sign,
                  calloc(fst->length, sizeof(unsigned int)), fst->length);

  bignum_t *cur_dividend = init_bignum(ZERO, NULL, 0);

  for (unsigned int i = 0; i < fst->length; i++) {
    cur_dividend->sign = snd->sign;
    cur_dividend->length += 1;
    unsigned int *realloc_digits = realloc(
        cur_dividend->digits, cur_dividend->length * sizeof(unsigned int));
    memmove(realloc_digits + 1, realloc_digits,
            (cur_dividend->length - 1) * sizeof(unsigned int));

    if (!realloc_digits) {
      free_bignum(res);
      free_bignum(cur_dividend);
      return NULL;
    }
    cur_dividend->digits = realloc_digits;

    realloc_digits[0] = fst->digits[fst->length - 1 - i];

    if (abs_is_greater_or_eq(cur_dividend, snd)) {
      int cur_quotient = find_cur_quotient(cur_dividend, snd);
      res->digits[res->length - 1 - i] = cur_quotient;

      bignum_t *bignum_cur_quotient = init_bignum_from_int(cur_quotient);
      bignum_t *tmp_mult = mult(snd, bignum_cur_quotient);
      bignum_t *tmp_diff = diff(cur_dividend, tmp_mult);

      free_bignum(cur_dividend);
      cur_dividend = tmp_diff;
      free_bignum(tmp_mult);
      free_bignum(bignum_cur_quotient);
    }
  }
  if (cur_dividend) free_bignum(cur_dividend);

  cut_zeros(res);

  return res;
}

bignum_t *mod(bignum_t *fst, bignum_t *snd) {
  bignum_t *tmp_div = divide(fst, snd);
  bignum_t *tmp_mult = mult(tmp_div, snd);
  bignum_t *res = diff(fst, tmp_mult);

  free_bignum(tmp_div);
  free_bignum(tmp_mult);

  if (res->sign == NEG) {
    bignum_t *tmp_add = add(res, snd);
    free_bignum(res);
    res = tmp_add;
  }

  return (res);
}

bignum_t *math_div(bignum_t *fst, bignum_t *snd) {
  bignum_t *tmp_mod = mod(fst, snd);
  bignum_t *tmp_diff = diff(fst, tmp_mod);
  free_bignum(tmp_mod);
  bignum_t *res = divide(tmp_diff, snd);
  free_bignum(tmp_diff);

  return res;
}