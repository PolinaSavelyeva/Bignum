#include "bignum.h"

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
