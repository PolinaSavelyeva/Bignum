#include "bignum.h"

#include <stdlib.h>

void
free_bignum (bignum_t *bignum)
{
  free (bignum->digits);
  free (bignum);
}