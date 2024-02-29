#include "math_op.h"

#include <stdlib.h>

#if 0
static void
compare (bignum_t *fst, bignum_t *snd, bignum_t *big, bignum_t *small)
{
  if (fst->sign > snd->sign)
    {
      big = fst;
      small = snd;
      return;
    }
  else if (fst->sign == snd->sign)
    {
      if (fst->length > snd->length)
        {
          if (fst->sign != NEG)
            {
              big = fst;
              small = snd;
              return;
            }
          else
            {
              big = snd;
              small = fst;
              return;
            }
        }
      else if (fst->length == snd->length)
        {
          for (int i = 0; i < fst->length; i++)
            {
              if (fst->digits[i] == snd->digits[i])
                {
                  continue;
                }
              else if (fst->digits[i] > snd->digits[i])
                {
                  if (fst->sign != NEG)
                    {
                      big = fst;
                      small = snd;
                      return;
                    }
                  else
                    {
                      big = snd;
                      small = fst;
                      return;
                    }
                }
              else
                {
                  if (fst->sign != NEG)
                    {
                      big = snd;
                      small = fst;
                      return;
                    }
                  else
                    {
                      big = fst;
                      small = snd;
                      return;
                    }
                }
              big = fst;
              small = snd;
              return;
            }
        }
      else if (fst->sign != NEG)
        {
          big = snd;
          small = fst;
          return;
        }
      else
        {
          big = fst;
          small = snd;
          return;
        }
    }
  else
    {
      big = snd;
      small = fst;
      return;
    }
}
#endif

static void
abs_compare (bignum_t *fst, bignum_t *snd, bignum_t **big, bignum_t **small)
{
  if (fst->length > snd->length)
    {
      *big = fst;
      *small = snd;
      return;
    }
  else if (fst->length == snd->length)
    {
      for (int i = 0; i < fst->length; i++)
        {
          if (fst->digits[i] == snd->digits[i])
            {
              continue;
            }
          else if (fst->digits[i] > snd->digits[i])
            {
              *big = fst;
              *small = snd;
              return;
            }
          else
            {
              *big = snd;
              *small = fst;
              return;
            }
        }
      *big = fst;
      *small = snd;
      return;
    }
  else
    {
      *big = snd;
      *small = fst;
      return;
    }
}

static void *
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
        return realloc (bignum->digits,
                        bignum->length * sizeof (unsigned int));
      bignum->digits = NULL;
      bignum->sign = ZERO;
      return bignum;
    }
  return bignum;
}

static int
math_div_ten (int num)
{
  int div = num / 10;
  return num < 0 ? div - 1 : div;
}

static int
math_mod_ten (int num)
{
  int mod = num % 10;
  return mod < 0 ? mod + 10 : mod;
}

bignum_t *
add (bignum_t *fst, bignum_t *snd)
{
  bignum_t *res = malloc (sizeof (bignum_t));
  bignum_t **big = malloc (sizeof (bignum_t *));
  bignum_t **small = malloc (sizeof (bignum_t *));

  abs_compare (fst, snd, big, small);

  unsigned int res_len = (*big)->length + 1;
  res->length = res_len;
  res->sign = (*big)->sign;

  unsigned int *res_digits = calloc (res_len, sizeof (unsigned int));
  res->digits = res_digits;

  int prev_sum = 0;
  for (int i = 0; i < (*small)->length; i++)
    {
      int cur_sum = (*big)->digits[i]
                    + (*big)->sign * (*small)->sign * (*small)->digits[i]
                    + prev_sum;

      res_digits[i] = math_mod_ten (cur_sum);
      prev_sum = math_div_ten (cur_sum);
    }

  for (int i = (*small)->length; i < (*big)->length; i++)
    {
      int cur_sum = (*big)->digits[i] + prev_sum;
      res_digits[i] = math_mod_ten (cur_sum);
      prev_sum = math_div_ten (cur_sum);
    }

  free (big);
  free (small);

  res_digits[res_len - 1] = res->sign * prev_sum;

  if (!cut_zeros (res))
    return NULL;
  return res;
}

bignum_t *
diff (bignum_t *fst, bignum_t *snd)
{
  bignum_t *op_snd = malloc(sizeof(bignum_t));
  if (snd->sign) 
  {
    op_snd->sign = snd->sign * NEG;
    op_snd->digits = snd->digits;
    op_snd->length = snd->length;

    bignum_t *ans = add (fst, op_snd);
    free(op_snd);
    return ans;
  }
  else if(!snd->length)
  {
    return fst;
  }
  else
  {
    return 0;
  }
}

// для умножения хватит n + m + 2 знаков
