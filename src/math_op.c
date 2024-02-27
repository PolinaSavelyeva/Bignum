#include "math_op.h"
#include <stdlib.h>

bignum_t *add(bignum_t *fst, bignum_t *snd)
{
    unsigned int length_max, length_min = 0;
    bignum_t *shorter, *longer = malloc(sizeof(bignum_t));
    
    if (fst->length < snd->length)
    {
        length_max = snd->length;
        length_min = fst->length;
        shorter = fst;
        longer = snd;
    }
    else
    {
        length_max = fst->length;
        length_min = snd->length;
        shorter = snd;
        longer = fst;
    }

    unsigned int *digits = malloc(length_max * sizeof(unsigned int));
    unsigned int previous_digit = 0;

    for (int i = 0; i < length_min; i++)
    {
        unsigned int sum = fst->digits[i] + snd->digits[i] + previous_digit;
        digits[i] = sum % 10;
        previous_digit = sum / 10;
    }

    for (int i = length_min; i < length_max; i++)
    {
        unsigned int sum = longer->digits[i] + previous_digit;
        digits[i] = sum % 10;
        previous_digit = sum / 10;
    }

    if (previous_digit)
    {
        digits = realloc(digits, length_max + 1);
        digits[length_max + 1] = previous_digit;
    }

    bignum_t *res = malloc(sizeof(bignum_t));

    res->sign = fst->sign;
    res->length = length_max + (previous_digit != 0);
    res->digits = digits;

    return res;
    
}