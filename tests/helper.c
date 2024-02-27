#include "helper.h"
#include "bignum.h"
#include <stdlib.h>
#include <string.h>

bignum_t *init_bignum_mods(bool sign, unsigned int length)
{
    unsigned int *digits = malloc(length * sizeof(unsigned int));
    bignum_t *bignum = malloc(sizeof(bignum_t));

    bignum->sign = sign;
    bignum->length = length;
    bignum->digits = digits;

    for (int i = 0; i < length; i++)
    {
        digits[length - i - 1] = (i + 1) % 10;
    }

    return bignum;
}

bignum_t *init_bignum_digits(bool sign, unsigned int *digits, unsigned int length)
{
    bignum_t *bignum = malloc(sizeof(bignum_t));

    bignum->sign = sign;
    bignum->length = length;
    bignum->digits = digits;

    return bignum;
}

bool is_equal(bignum_t *bignum_fst, bignum_t *bignum_snd)
{
    return (bignum_fst->sign == bignum_snd->sign &&
            bignum_fst->length == bignum_snd->length &&
            !memcmp(bignum_fst->digits, bignum_snd->digits, bignum_fst->length * sizeof(unsigned int)));
}

void free_bignum(bignum_t *bignum)
{
    free(bignum->digits);
    free(bignum);
}