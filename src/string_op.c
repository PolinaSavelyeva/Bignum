#include "string_op.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static bool parse_ch_sign(char ch_sign)
{

    if (ch_sign == '-' || ch_sign == '+' || isdigit(ch_sign))
    {
        return ch_sign == '-';
    }
    else
    {
        return NULL;
    }
}

bignum_t *to_bignum(char *str)
{
    bignum_t *bignum = malloc(sizeof(bignum_t));
    bignum->sign = parse_ch_sign(str[0]);
    unsigned int fst_digit_index = str[0] == '+' || str[0] == '-' ? 1 : 0;
    bignum->length = strlen(str) - fst_digit_index;

    if (bignum->length)
    {
        unsigned int *digits = malloc(bignum->length * sizeof(unsigned int));
        bignum->digits = digits;

        for (int i = 0; i < bignum->length; i++)
        {
            unsigned int str_index = bignum->length - i - 1 + fst_digit_index;

            if (isdigit(str[str_index]))
            {
                digits[i] = str[str_index] - '0';
            }
            else
            {
                return NULL;
            }
        }
    }
    else
    {
        return NULL;
    }

    return bignum;
}

char *to_str(bignum_t *bignum)
{
    unsigned int fst_digit_index = bignum->sign;
    char *str = malloc((bignum->length + 1 + fst_digit_index) * sizeof(char));

    if (fst_digit_index)
    {
        str[0] = '-';
    }

    for (int i = fst_digit_index; i < bignum->length + fst_digit_index; i++)
    {
        str[i] = bignum->digits[bignum->length - i - 1 + fst_digit_index] + '0';
    }

    str[bignum->length + fst_digit_index] = '\0';

    return str;
}