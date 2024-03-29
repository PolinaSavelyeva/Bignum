#include <stdlib.h>

#include "helper.h"
#include "math_op.h"
#include "minunit.h"

#define TEST_ADD_STR_EQ(sign_fst, len_fst, sign_snd, len_snd, str)     \
  mu_check(test_op_res_eq_str(bignum_add, sign_fst, len_fst, sign_snd, \
                              len_snd, str))

#define TEST_ADD_INTS_EQ(i_fst, i_snd, i_ans) \
  mu_check(test_op_res_eq_int(bignum_add, i_fst, i_snd, i_ans))

#define TEST_DIFF_STR_EQ(sign_fst, len_fst, sign_snd, len_snd, str)     \
  mu_check(test_op_res_eq_str(bignum_diff, sign_fst, len_fst, sign_snd, \
                              len_snd, str))

#define TEST_DIFF_INT_EQ(i_fst, i_snd, i_ans) \
  mu_check(test_op_res_eq_int(bignum_diff, i_fst, i_snd, i_ans))

#define TEST_MULT_INT_EQ(i_fst, i_snd, i_ans) \
  mu_check(test_op_res_eq_int(bignum_mult, i_fst, i_snd, i_ans))

#define TEST_DIV_INT_EQ(i_fst, i_snd, i_ans) \
  mu_check(test_op_res_eq_int(bignum_div, i_fst, i_snd, i_ans))

#define TEST_MOD_INT_EQ(i_fst, i_snd, i_ans) \
  mu_check(test_op_res_eq_int(bignum_mod, i_fst, i_snd, i_ans))

MU_TEST(add_eq_neg) { TEST_ADD_STR_EQ(NEG, 5, NEG, 5, "-24690"); }

MU_TEST(add_eq_pos) { TEST_ADD_STR_EQ(POS, 1, POS, 1, "2"); }

MU_TEST(add_neg_dif_len) { TEST_ADD_STR_EQ(NEG, 5, NEG, 4, "-13579"); }

MU_TEST(add_pos_dif_len) { TEST_ADD_STR_EQ(POS, 3, POS, 11, "12345679024"); }

MU_TEST(add_eq_pos_neg) { TEST_ADD_STR_EQ(POS, 2, NEG, 2, "0"); }

MU_TEST(add_eq_neg_pos) { TEST_ADD_STR_EQ(NEG, 2, POS, 2, "0"); }

MU_TEST(add_pos_neg_dif_len) {
  TEST_ADD_STR_EQ(NEG, 10, POS, 4, "-1234566656");
}

MU_TEST(add_zero_neg) { TEST_ADD_STR_EQ(ZERO, 0, NEG, 7, "-1234567"); }

MU_TEST(add_zero_pos) { TEST_ADD_STR_EQ(POS, 10, NEG, 0, "1234567890"); }

MU_TEST(add_without_realloc) { TEST_ADD_INTS_EQ(999, 1, 1000); }

MU_TEST_SUITE(add_tests) {
  MU_RUN_TEST(add_eq_neg);
  MU_RUN_TEST(add_eq_pos);
  MU_RUN_TEST(add_pos_dif_len);
  MU_RUN_TEST(add_neg_dif_len);
  MU_RUN_TEST(add_eq_pos_neg);
  MU_RUN_TEST(add_eq_neg_pos);
  MU_RUN_TEST(add_pos_neg_dif_len);
  MU_RUN_TEST(add_zero_neg);
  MU_RUN_TEST(add_zero_pos);
  MU_RUN_TEST(add_without_realloc);
}

MU_TEST(diff_eq_neg) { TEST_DIFF_STR_EQ(NEG, 5, NEG, 5, "0"); }

MU_TEST(diff_eq_pos) { TEST_DIFF_STR_EQ(POS, 1, POS, 1, "0"); }

MU_TEST(diff_neg_dif_len) { TEST_DIFF_STR_EQ(NEG, 5, NEG, 4, "-11111"); }

MU_TEST(diff_pos_dif_len) { TEST_DIFF_STR_EQ(POS, 3, POS, 11, "-12345678778"); }

MU_TEST(diff_eq_pos_neg) { TEST_DIFF_INT_EQ(2, -2, 4); }

MU_TEST(diff_pos_neg_dif_len) {
  TEST_DIFF_STR_EQ(NEG, 10, POS, 4, "-1234569124");
}

MU_TEST(diff_zero_neg) { TEST_DIFF_INT_EQ(0, -7, 7); }

MU_TEST(diff_zero_pos) { TEST_DIFF_STR_EQ(POS, 10, ZERO, 0, "1234567890"); }

MU_TEST(diff_with_realloc) { TEST_DIFF_INT_EQ(1000, 1, 999); }

MU_TEST(diff_one) { TEST_DIFF_INT_EQ(1, 1, 0); }

MU_TEST_SUITE(diff_tests) {
  MU_RUN_TEST(diff_eq_neg);
  MU_RUN_TEST(diff_eq_pos);
  MU_RUN_TEST(diff_pos_dif_len);
  MU_RUN_TEST(diff_neg_dif_len);
  MU_RUN_TEST(diff_eq_pos_neg);
  MU_RUN_TEST(diff_pos_neg_dif_len);
  MU_RUN_TEST(diff_zero_neg);
  MU_RUN_TEST(diff_zero_pos);
  MU_RUN_TEST(diff_with_realloc);
  MU_RUN_TEST(diff_one);
}

MU_TEST(mult_one_digit_neg) { TEST_MULT_INT_EQ(-5, -5, 25); }

MU_TEST(mult_one_digit_pos) { TEST_MULT_INT_EQ(1, 1, 1); }

MU_TEST(mult_one_digit_pos_neg) { TEST_MULT_INT_EQ(7, -7, -49); }

MU_TEST(mult_zero_pos) { TEST_MULT_INT_EQ(0, 726, 0); }

MU_TEST(mult_zero_neg) { TEST_MULT_INT_EQ(0, -929, 0); }

MU_TEST(mult_pos_neg) { TEST_MULT_INT_EQ(-127, 61, -7747); }

MU_TEST(mult_neg_neg) { TEST_MULT_INT_EQ(-1278, -74, 94572); }

MU_TEST_SUITE(mult_tests) {
  MU_RUN_TEST(mult_one_digit_neg);
  MU_RUN_TEST(mult_one_digit_pos);
  MU_RUN_TEST(mult_one_digit_pos_neg);
  MU_RUN_TEST(mult_zero_pos);
  MU_RUN_TEST(mult_zero_neg);
  MU_RUN_TEST(mult_pos_neg);
  MU_RUN_TEST(mult_neg_neg);
}

MU_TEST(div_eq_neg) { TEST_DIV_INT_EQ(-5, -5, 1); }

MU_TEST(div_eq_pos) { TEST_DIV_INT_EQ(178, 178, 1); }

MU_TEST(div_pos_one) { TEST_DIV_INT_EQ(219283, 1, 219283); }

MU_TEST(div_neg_one) { TEST_DIV_INT_EQ(-1281872, 1, -1281872); }

MU_TEST(div_zero_pos) { TEST_DIV_INT_EQ(0, 929, 0); }

MU_TEST(div_zero_neg) { TEST_DIV_INT_EQ(0, -61, 0); }

MU_TEST(div_pos) { TEST_DIV_INT_EQ(233, 1, 233); }

MU_TEST(div_neg) { TEST_DIV_INT_EQ(-5, 2, -3); }

MU_TEST(div_special) { TEST_DIV_INT_EQ(4100, 588, 6); }

MU_TEST(div_res_zero) { TEST_DIV_INT_EQ(-7, 8, -1); }

MU_TEST_SUITE(div_tests) {
  MU_RUN_TEST(div_eq_neg);
  MU_RUN_TEST(div_eq_pos);
  MU_RUN_TEST(div_pos_one);
  MU_RUN_TEST(div_neg_one);
  MU_RUN_TEST(div_zero_pos);
  MU_RUN_TEST(div_zero_neg);
  MU_RUN_TEST(div_pos);
  MU_RUN_TEST(div_neg);
  MU_RUN_TEST(div_special);
  MU_RUN_TEST(div_res_zero);
}

MU_TEST(mod_eq_neg) { TEST_MOD_INT_EQ(-5, -5, 0); }

MU_TEST(mod_eq_pos) { TEST_MOD_INT_EQ(178, 178, 0); }

MU_TEST(mod_pos_one) { TEST_MOD_INT_EQ(219283, 1, 0); }

MU_TEST(mod_neg_one) { TEST_MOD_INT_EQ(-1281872, 1, 0); }

MU_TEST(mod_zero_pos) { TEST_MOD_INT_EQ(0, 929, 0); }

MU_TEST(mod_zero_neg) { TEST_MOD_INT_EQ(0, -61, 0); }

MU_TEST(mod_neg) { TEST_MOD_INT_EQ(445, -4, 1); }

MU_TEST(mod_special) { TEST_MOD_INT_EQ(4100, 588, 572); }

MU_TEST_SUITE(mod_tests) {
  MU_RUN_TEST(mod_eq_neg);
  MU_RUN_TEST(mod_eq_pos);
  MU_RUN_TEST(mod_pos_one);
  MU_RUN_TEST(mod_neg_one);
  MU_RUN_TEST(mod_zero_pos);
  MU_RUN_TEST(mod_zero_neg);
  MU_RUN_TEST(mod_neg);
  MU_RUN_TEST(mod_special);
}

int main() {
  MU_RUN_SUITE(add_tests);
  MU_RUN_SUITE(diff_tests);
  MU_RUN_SUITE(mult_tests);
  MU_RUN_SUITE(div_tests);
  MU_RUN_SUITE(mod_tests);
  MU_REPORT();
  return MU_EXIT_CODE;
}
