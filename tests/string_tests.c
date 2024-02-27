#include "minunit.h"
#include "string_op.h"
#include "helper.h"
#include <stdlib.h>

#define TEST_BIGNUM_EQ(str, val, len) bignum_t *bignum = init_bignum_mods(val, len); \
    mu_check(is_equal(bignum, to_bignum(str))); \
    free_bignum(bignum); \

MU_TEST(to_bignum_small_negative)
{
    TEST_BIGNUM_EQ("-123", 1, 3);
}

MU_TEST(to_bignum_small_positive_unsigned)
{
    TEST_BIGNUM_EQ("1234567", 0, 7);
}

MU_TEST(to_bignum_small_positive_signed)
{
    TEST_BIGNUM_EQ("+1234567", 0, 7);
}

MU_TEST(to_bignum_big_negative)
{
    TEST_BIGNUM_EQ("-123456789012345", 1, 15);
}

MU_TEST(to_bignum_big_positive)
{
    TEST_BIGNUM_EQ("1234567890", 0, 10);
}

MU_TEST_SUITE(to_bignum_tests)
{
    MU_RUN_TEST(to_bignum_small_negative);
    MU_RUN_TEST(to_bignum_small_positive_unsigned);
    MU_RUN_TEST(to_bignum_small_positive_signed);
    MU_RUN_TEST(to_bignum_big_negative);
    MU_RUN_TEST(to_bignum_big_positive);
}

#define TEST_STR_EQ(str, val, len) bignum_t *bignum = init_bignum_mods(val, len); \
    mu_assert_string_eq(to_str(bignum), str);\
    free_bignum(bignum); \

MU_TEST(to_str_small_negative)
{
    TEST_STR_EQ("-123", 1, 3);
}

MU_TEST(to_str_small_positive)
{
    TEST_STR_EQ("1234567", 0, 7);
}

MU_TEST(to_str_big_negative)
{
    TEST_STR_EQ("-123456789012345", 1, 15);
}

MU_TEST(to_str_big_positive)
{
    TEST_STR_EQ("1234567890", 0, 10);
}

MU_TEST_SUITE(to_str_tests)
{
    MU_RUN_TEST(to_str_small_negative);
    MU_RUN_TEST(to_str_small_positive);
    MU_RUN_TEST(to_str_big_negative);
    MU_RUN_TEST(to_str_big_positive);
}

int main()
{
    MU_RUN_SUITE(to_bignum_tests);
    MU_RUN_SUITE(to_str_tests);
    MU_REPORT();
    return MU_EXIT_CODE;
}
