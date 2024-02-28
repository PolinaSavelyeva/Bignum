#include "string_op.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static void *parse_fst_char(char fst_ch, sign_t *sign, unsigned int *fst_digit_i)
{
    if (fst_ch == '-' || fst_ch == '+')
    {
        *sign = fst_ch == '-' ? NEG : POS;
        *fst_digit_i = 1;
    }
    else if (isdigit(fst_ch))
    {
        *sign = fst_ch == '0' ? ZERO : POS;
    }
    else
    {
        return NULL;
    }
}

static void *cut_zeros(bignum_t *bignum)
{
    unsigned int len_to_cut = 0;

    for (int i = bignum->length - 1; i >= 0; i--)
    {
        if (!bignum->digits[i])
            len_to_cut++;
        else
            break;
    }

    if (len_to_cut)
    {
        bignum->length -= len_to_cut;
        return realloc(bignum->digits, bignum->length - len_to_cut);
    }
}

bignum_t *to_bignum(char *str)
{
    bignum_t *bignum = malloc(sizeof(bignum_t));
    unsigned int fst_digit_i = 0;
    parse_fst_char(str[0], &(bignum->sign), &fst_digit_i);

    if (bignum->sign && str[1]=='0')
    {
        return NULL;
    }

    bignum->length = strlen(str) - fst_digit_i  - 1 + bignum->sign * bignum->sign;

    if (bignum->length && str[1]!='0' || !bignum->sign && !bignum->length)
    {
        unsigned int *digits = malloc(bignum->length * sizeof(unsigned int));
        bignum->digits = digits;

        for (int i = 0; i < bignum->length; i++)
        {
            unsigned int str_i = bignum->length - i - 1 + fst_digit_i;

            if (isdigit(str[str_i]))
            {
                digits[i] = str[str_i] - '0';
            }
            else
            {
                return NULL;
            }
        }
        return bignum;
    }
    else
    {
        return NULL;
    }
}

char *to_str(bignum_t *bignum)
{
    if (bignum->sign)
    {
        if (!bignum->length)
            return NULL;

        unsigned int fst_digit_i = bignum->sign == NEG;
        char *str = malloc((bignum->length + 1 + fst_digit_i) * sizeof(char));

        if (fst_digit_i)
        {
            str[0] = '-';
        }

        for (int i = fst_digit_i; i < bignum->length + fst_digit_i; i++)
        {
            str[i] = bignum->digits[bignum->length - i - 1 + fst_digit_i] + '0';
        }

        str[bignum->length + fst_digit_i] = '\0';
        return str;
    }
    else if (!bignum->length)
    {
        char *str = malloc(2);
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
    else
    {
        return NULL;
    }
}