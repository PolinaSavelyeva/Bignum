#include "math_op.h"

#include <stdio.h>
#include <stdlib.h>

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
      for (int i = fst->length - 1; i >= 0; i--)
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

  int carry = 0;
  for (int i = 0; i < (*small)->length; i++)
    {
      int cur_sum = (*big)->digits[i]
                    + (*big)->sign * (*small)->sign * (*small)->digits[i]
                    + carry;

      res_digits[i] = math_mod_ten (cur_sum);
      carry = math_div_ten (cur_sum);
    }

  for (int i = (*small)->length; i < (*big)->length; i++)
    {
      int cur_sum = (*big)->digits[i] + carry;
      res_digits[i] = math_mod_ten (cur_sum);
      carry = math_div_ten (cur_sum);
    }

  free (big);
  free (small);

  res_digits[res_len - 1] = res->sign * carry;

  if (!cut_zeros (res))
    return NULL;
  return res;
}

bignum_t *
diff (bignum_t *fst, bignum_t *snd)
{
  bignum_t *op_sign_snd = malloc (sizeof (bignum_t));

  op_sign_snd->sign = snd->sign * NEG;
  op_sign_snd->digits = snd->digits;
  op_sign_snd->length = snd->length;

  bignum_t *ans = add (fst, op_sign_snd);
  free (op_sign_snd);
  return ans;
}

bignum_t *
mult (bignum_t *fst, bignum_t *snd)
{

  bignum_t *res = malloc (sizeof (bignum_t));
  unsigned int res_len = fst->length + snd->length + 2;
  unsigned int *res_digits = calloc (res_len, sizeof (unsigned int));

  res->sign = fst->sign * snd->sign;
  res->length = res_len;
  res->digits = res_digits;

  for (int i = 0; i < fst->length; i++)
    {
      unsigned int carry = 0;
      for (int j = 0; j < snd->length; j++)
        {
          unsigned int sum
              = fst->digits[i] * snd->digits[j] + res_digits[i + j] + carry;
          res_digits[i + j] = sum % 10;
          carry = sum / 10;
        }
      res_digits[i + snd->length] = carry;
    }

  cut_zeros (res);

  return res;
}