#include "bignum.h"

#include <math.h>
#include <stdlib.h>

void
free_bignum (bignum_t *bignum)
{
  free (bignum->digits);
  free (bignum);
}

void *
cut_zeros (bignum_t *bignum)
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
      if (bignum->length)
        {
          void *realloc_digits = realloc (
              bignum->digits, bignum->length * sizeof (unsigned int));

          // Checks for potential memory leaks when realloc returns NULL
          if (!realloc_digits)
            free (bignum->digits);
          bignum->digits = realloc_digits;
        }
      else
        {
          free (bignum->digits);

          bignum->digits = NULL;
          bignum->sign = ZERO;
        }
    }
  return bignum;
}

bignum_t *
init_bignum_from_int (int num)
{
  bignum_t *bignum = malloc (sizeof (bignum_t));
  bignum->sign = (num > 0) - (num < 0);
  bignum->length = num ? (unsigned int)log10 (abs (num)) + 1 : 0;
  unsigned int *digits = malloc (bignum->length * sizeof (unsigned int));
  bignum->digits = digits;
  num = abs (num);

  for (int i = 0; i < bignum->length; i++)
    {
      bignum->digits[i] = num % 10;
      num /= 10;
    }

  return bignum;
}