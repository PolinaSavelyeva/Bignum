#include <stdlib.h>

#include "helper.h"
#include "math_op.h"
#include "minunit.h"
#include "string_op.h"

// int -> bignum -> int
#define FREE_ALL    \
  free_bignum(fst); \
  free_bignum(snd); \
  free_bignum(res)

#define TEST_ADD_EQ(sign_fst, length_fst, sign_snd, length_snd, ans_str) \
  bignum_t *fst = init_bignum_mods(sign_fst, length_fst);                \
  bignum_t *snd = init_bignum_mods(sign_snd, length_snd);                \
  bignum_t *res = to_bignum(ans_str);                                    \
  mu_check(is_equal(add(fst, snd), res));                                \
  FREE_ALL

MU_TEST(add_negative_same_length) { TEST_ADD_EQ(1, 5, 1, 5, "-24690"); }

MU_TEST(add_positive_same_length) {
  TEST_ADD_EQ(0, 15, 0, 15, "246913578024690");
}

MU_TEST(add_negative) { TEST_ADD_EQ(1, 5, 1, 4, "-13579"); }

MU_TEST(add_positive) { TEST_ADD_EQ(0, 3, 0, 11, "12345679024"); }

MU_TEST_SUITE(add_tests) {
  MU_RUN_TEST(add_negative_same_length);
  MU_RUN_TEST(add_positive_same_length);
  MU_RUN_TEST(add_positive);
  MU_RUN_TEST(add_negative);
}

int main() {
  MU_RUN_SUITE(add_tests);
  MU_REPORT();
  return MU_EXIT_CODE;
}
