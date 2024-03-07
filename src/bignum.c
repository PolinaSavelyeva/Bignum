#include "bignum.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void free_bignum(bignum_t *bignum) {
  free(bignum->digits);
  free(bignum);
}

bignum_t *init_bignum(sign_t sign, unsigned int length) {
  bignum_t *bignum = malloc(sizeof(*bignum));

  bignum->sign = sign;
  bignum->length = length;
  bignum->digits = calloc(length, sizeof(unsigned int));

  return bignum;
}

void normalize_bignum(bignum_t *bignum) {
  unsigned int len_to_cut = 0;

  for (int i = bignum->length - 1; i >= 0; i--) {
    if (!bignum->digits[i])
      len_to_cut++;
    else
      break;
  }

  if (len_to_cut) {
    bignum->length -= len_to_cut;
    if (bignum->length) {
      void *realloc_digits =
          realloc(bignum->digits, bignum->length * sizeof(unsigned int));

      if (realloc_digits) bignum->digits = realloc_digits;
    } else {
      free(bignum->digits);

      bignum->digits = NULL;
      bignum->sign = ZERO;
    }
  }
}

bignum_t *init_bignum_from_int(int num) {
  int len = num ? (unsigned int)log10(abs(num)) + 1 : 0;

  bignum_t *bignum = init_bignum((num > 0) - (num < 0), len);

  num = abs(num);

  for (int i = 0; i < bignum->length; i++) {
    bignum->digits[i] = num % 10;
    num /= 10;
  }

  return bignum;
}

bignum_t *init_bignum_with_digits(sign_t sign, unsigned int *digits,
                                  unsigned int length) {
  bignum_t *bignum = malloc(sizeof(*bignum));

  bignum->sign = sign;
  bignum->length = length;
  bignum->digits = digits;

  return bignum;
}

bool bignums_are_equal(bignum_t *bignum_fst, bignum_t *bignum_snd) {
  return (bignum_fst->sign == bignum_snd->sign &&
          bignum_fst->length == bignum_snd->length &&
          !memcmp(bignum_fst->digits, bignum_snd->digits,
                  bignum_fst->length * sizeof(unsigned int)));
}

bignum_t *bignum_copy(bignum_t *src) {
  bignum_t *dest = init_bignum(src->sign * src->sign, src->length);
  memcpy(dest->digits, src->digits, dest->length * sizeof(unsigned int));

  return dest;
}