#include "helper.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"

bignum_t *init_bignum_mods(sign_t sign, unsigned int length) {
  unsigned int *digits = malloc(length * sizeof(unsigned int));
  bignum_t *bignum = malloc(sizeof(bignum_t));

  bignum->sign = sign;
  bignum->length = length;
  bignum->digits = digits;

  for (int i = 0; i < length; i++) {
    digits[length - i - 1] = (i + 1) % 10;
  }

  return bignum;
}

bignum_t *init_bignum_digits(sign_t sign, unsigned int *digits,
                             unsigned int length) {
  bignum_t *bignum = malloc(sizeof(bignum_t));

  bignum->sign = sign;
  bignum->length = length;
  bignum->digits = digits;

  return bignum;
}

bignum_t *init_bignum_int(int num) {
  bignum_t *bignum = malloc(sizeof(bignum_t));
  bignum->sign = (num > 0) - (num < 0);
  bignum->length = num ? (unsigned int)log10(num) + 1 : 0;
  unsigned int *digits = malloc(bignum->length * sizeof(unsigned int));
  bignum->digits = digits;
  num = abs(num);

  for (int i = 0; i < bignum->length; i++) {
    bignum->digits[i] = num % 10;
    num /= 10;
  }

  return bignum;
}

bool is_equal(bignum_t *bignum_fst, bignum_t *bignum_snd) {
  return (bignum_fst->sign == bignum_snd->sign &&
          bignum_fst->length == bignum_snd->length &&
          !memcmp(bignum_fst->digits, bignum_snd->digits,
                  bignum_fst->length * sizeof(unsigned int)));
}