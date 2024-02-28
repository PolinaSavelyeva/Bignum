#include "string_op.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int parse_fst_char(char fst_ch, sign_t *sign,
                          unsigned int *fst_digit_i) {
  if (fst_ch == '-' || fst_ch == '+') {
    *sign = fst_ch == '-' ? NEG : POS;
    *fst_digit_i = 1;

    return 0;
  } else if (isdigit(fst_ch)) {
    *sign = fst_ch == '0' ? ZERO : POS;
    return 0;
  } else {
    return 1;
  }
}

bignum_t *to_bignum(char *str) {
  bignum_t *bignum = malloc(sizeof(bignum_t));
  unsigned int fst_digit_i = 0;
  int exit_code = parse_fst_char(str[0], &(bignum->sign), &fst_digit_i);

  if ((bignum->sign && str[1] == '0') || exit_code) {
    free(bignum);
    return NULL;
  }

  bignum->length = strlen(str) - fst_digit_i - 1 + bignum->sign * bignum->sign;

  if ((bignum->length && str[1] != '0') || (!bignum->sign && !bignum->length)) {
    unsigned int *digits = malloc(bignum->length * sizeof(unsigned int));
    bignum->digits = digits;

    for (int i = 0; i < bignum->length; i++) {
      unsigned int str_i = bignum->length - i - 1 + fst_digit_i;

      if (isdigit(str[str_i])) {
        digits[i] = str[str_i] - '0';
      } else {
        free_bignum(bignum);
        return NULL;
      }
    }
    return bignum;
  } else {
    free(bignum);
    return NULL;
  }
}

char *to_str(bignum_t *bignum) {
  if (bignum->sign) {
    if (!bignum->length)
      return NULL;

    unsigned int fst_digit_i = bignum->sign == NEG;
    char *str = malloc((bignum->length + 1 + fst_digit_i) * sizeof(char));

    if (fst_digit_i) {
      str[0] = '-';
    }

    for (int i = fst_digit_i; i < bignum->length + fst_digit_i; i++) {
      str[i] = bignum->digits[bignum->length - i - 1 + fst_digit_i] + '0';
    }

    str[bignum->length + fst_digit_i] = '\0';
    return str;
  } else if (!bignum->length) {
    char *str = malloc(2);
    str[0] = '0';
    str[1] = '\0';
    return str;
  } else {
    return NULL;
  }
}