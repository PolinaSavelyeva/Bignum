#include "string_op.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static bool parse_sign(char *str)
{

    if (str == "-" || str == "+" || isdigit(str))
    {
        return (str == "-");
    }
    else
    {
        printf("Invalid input. Digit or '+', '-' were expected");
        abort();
    }
}

bignum_t *to_bignum(char *str)
{

    bignum_t *bignum;
    bool sign;
    unsigned int length;

    bignum = malloc(sizeof(bignum_t));
    sign = parse_sign(str);
    length = strlen(str);

    if (length)
    {
        bignum->sign = sign;
        bignum->length = length - sign;

        for (int i = sign; i < length; i++)
        {
            if (isdigit(str[i]))
            {
                bignum->digits[i] = str[i];
            }
            else
            {
                printf("Invalid input. String of digits was expected");
                abort();
            }
        }
    }

    return bignum;
}