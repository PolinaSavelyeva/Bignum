#include <stdlib.h>

#include "helper.h"
#include "math_op.h"
#include "minunit.h"
#include "string_op.h"

#define TEST_ADD_EQ(sign_fst, length_fst, sign_snd, length_snd, ans_str)      \
  bignum_t *fst = init_bignum_mods (sign_fst, length_fst);                    \
  bignum_t *snd = init_bignum_mods (sign_snd, length_snd);                    \
  bignum_t *expect = to_bignum (ans_str);                                     \
  bignum_t *actual = add (fst, snd);                                          \
  mu_check (is_equal (actual, expect));                                       \
  free_bignum (fst);                                                          \
  free_bignum (snd);                                                          \
  free_bignum (expect);                                                       \
  free_bignum (actual)

MU_TEST (add_eq_neg) { TEST_ADD_EQ (NEG, 5, NEG, 5, "-24690"); }

MU_TEST (add_eq_pos) { TEST_ADD_EQ (POS, 1, POS, 1, "2"); }

MU_TEST (add_neg_dif_len) { TEST_ADD_EQ (NEG, 5, NEG, 4, "-13579"); }

MU_TEST (add_pos_dif_len) { TEST_ADD_EQ (POS, 3, POS, 11, "12345679024"); }

MU_TEST (add_eq_pos_neg) { TEST_ADD_EQ (POS, 2, NEG, 2, "0"); }

MU_TEST (add_pos_neg_dif_len) { TEST_ADD_EQ (NEG, 10, POS, 4, "-1234566656"); }

MU_TEST (add_zero_neg) { TEST_ADD_EQ (ZERO, 0, NEG, 7, "-1234567"); }

MU_TEST (add_zero_pos) { TEST_ADD_EQ (POS, 10, NEG, 0, "1234567890"); }

MU_TEST (add_without_realloc)
{

  bignum_t *bignum_fst = init_bignum_int (999);
  bignum_t *bignum_snd = init_bignum_int (1);
  bignum_t *expect = init_bignum_int (1000);
  bignum_t *actual = add (bignum_fst, bignum_snd);
  mu_check (is_equal (expect, actual));
  free_bignum (bignum_fst);
  free_bignum (bignum_snd);
  free_bignum (expect);
  free_bignum (actual);
}

MU_TEST_SUITE (add_tests)
{
  MU_RUN_TEST (add_eq_neg);
  MU_RUN_TEST (add_eq_pos);
  MU_RUN_TEST (add_pos_dif_len);
  MU_RUN_TEST (add_neg_dif_len);
  MU_RUN_TEST (add_eq_pos_neg);
  MU_RUN_TEST (add_pos_neg_dif_len);
  MU_RUN_TEST (add_zero_neg);
  MU_RUN_TEST (add_zero_pos);
  MU_RUN_TEST (add_without_realloc);
}

int
main ()
{
  MU_RUN_SUITE (add_tests);
  MU_REPORT ();
  return MU_EXIT_CODE;
}
