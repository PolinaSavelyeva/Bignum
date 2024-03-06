#include <stdlib.h>

#include "minunit.h"
#include "utils.h"

#define TEST_EUCLID_ALG_EQ(i_fst, i_snd, i_ans) \
  mu_check(test_op_res_eq_int(euclidean_alg, i_fst, i_snd, i_ans))

MU_TEST(euclid_composites) { TEST_EUCLID_ALG_EQ(30, 18, 6); }

MU_TEST(euclid_primes) { TEST_EUCLID_ALG_EQ(607, 233, 1); }

MU_TEST(euclid_zero) { TEST_EUCLID_ALG_EQ(0, 233, 233); }

MU_TEST(euclid_neg) { TEST_EUCLID_ALG_EQ(-1, 233, 1); }

MU_TEST(euclid_special) { TEST_EUCLID_ALG_EQ(40, 80, 40); }

MU_TEST_SUITE(euclidean_alg_test) {
  MU_RUN_TEST(euclid_composites);
  MU_RUN_TEST(euclid_primes);
  MU_RUN_TEST(euclid_zero);
  MU_RUN_TEST(euclid_neg);
  MU_RUN_TEST(euclid_special);
}

int main() {
  MU_RUN_SUITE(euclidean_alg_test);
  MU_REPORT();
  return MU_EXIT_CODE;
}
