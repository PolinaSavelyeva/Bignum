#include "minunit.h"
#include "string_op.h"
#include "helper.h"
#include <stdlib.h>

#define TEST_BIGNUM_EQ(str, val, len)              \
    bignum_t *bignum = init_bignum_mods(val, len); \
    mu_check(is_equal(bignum, to_bignum(str)));    \
    free_bignum(bignum)

#define TEST_BIGNUM_FAIL(str, val, len) \
    mu_check(NULL == to_bignum(str))

MU_TEST(to_bignum_small_neg)
{
    TEST_BIGNUM_EQ("-123", NEG, 3);
}

MU_TEST(to_bignum_small_pos_unsigned)
{
    TEST_BIGNUM_EQ("1234567", POS, 7);
}

MU_TEST(to_bignum_small_pos_signed)
{
    TEST_BIGNUM_EQ("+1234567", POS, 7);
}

MU_TEST(to_bignum_big_neg)
{
    TEST_BIGNUM_EQ("-123456789012345", NEG, 15);
}

MU_TEST(to_bignum_big_pos)
{
    TEST_BIGNUM_EQ("1234567890", POS, 10);
}

MU_TEST(to_bignum_zero)
{
    TEST_BIGNUM_EQ("0", ZERO, 0);
}

MU_TEST(to_bignum_pos_zero)
{
    TEST_BIGNUM_FAIL("+0", ZERO, 0);
}

MU_TEST(to_bignum_neg_zero)
{
    TEST_BIGNUM_FAIL("-0", ZERO, 0);
}

MU_TEST(to_bignum_many_zeros)
{
    TEST_BIGNUM_FAIL("000", ZERO, 0);
}

MU_TEST(to_bignum_begin_zero)
{
    TEST_BIGNUM_FAIL("+0001234567", POS, 7);
}

MU_TEST(to_bignum_one)
{
    TEST_BIGNUM_EQ("1", POS, 1);
}

MU_TEST(to_bignum_non_digit)
{
    mu_check(to_bignum("+abc") == NULL);
}

MU_TEST(to_bignum_one_alpha)
{
    mu_check(to_bignum("98189819283h9181928") == NULL);
}

MU_TEST_SUITE(to_bignum_tests)
{
    MU_RUN_TEST(to_bignum_small_neg);
    MU_RUN_TEST(to_bignum_small_pos_unsigned);
    MU_RUN_TEST(to_bignum_small_pos_signed);
    MU_RUN_TEST(to_bignum_big_neg);
    MU_RUN_TEST(to_bignum_big_pos);
    MU_RUN_TEST(to_bignum_zero);
    MU_RUN_TEST(to_bignum_pos_zero);
    MU_RUN_TEST(to_bignum_neg_zero);
    MU_RUN_TEST(to_bignum_many_zeros);
    MU_RUN_TEST(to_bignum_begin_zero);
    MU_RUN_TEST(to_bignum_one);
    MU_RUN_TEST(to_bignum_non_digit);
    MU_RUN_TEST(to_bignum_one_alpha);
}

#define TEST_STR_EQ(str, val, len)                 \
    bignum_t *bignum = init_bignum_mods(val, len); \
    mu_assert_string_eq(to_str(bignum), str);      \
    free_bignum(bignum);

#define TEST_STR_FAIL(str, val, len) \
    mu_check(NULL == to_bignum(str))

MU_TEST(to_str_small_negative)
{
    TEST_STR_EQ("-123", NEG, 3);
}

MU_TEST(to_str_small_positive)
{
    TEST_STR_EQ("1234567", POS, 7);
}

MU_TEST(to_str_big_negative)
{
    TEST_STR_EQ("-123456789012345", NEG, 15);
}

MU_TEST(to_str_big_positive)
{
    TEST_STR_EQ("1234567890", POS, 10);
}

MU_TEST(to_str_zero)
{
    TEST_STR_EQ("0", ZERO, 0);
}

MU_TEST(to_str_pos_zero)
{
    TEST_STR_FAIL("+0", ZERO, 0);
}

MU_TEST(to_str_neg_zero)
{
    TEST_STR_FAIL("-0", ZERO, 0);
}

MU_TEST(to_str_begin_zero)
{
    TEST_STR_FAIL("+0001234567", POS, 7);
}

MU_TEST(to_str_one)
{
    TEST_STR_EQ("1", POS, 1);
}

MU_TEST_SUITE(to_str_tests)
{
    MU_RUN_TEST(to_str_small_negative);
    MU_RUN_TEST(to_str_small_positive);
    MU_RUN_TEST(to_str_big_negative);
    MU_RUN_TEST(to_str_big_positive);
    MU_RUN_TEST(to_str_zero);
    MU_RUN_TEST(to_str_begin_zero);
    MU_RUN_TEST(to_str_neg_zero);
    MU_RUN_TEST(to_str_one);
    MU_RUN_TEST(to_str_pos_zero);
}

int main()
{
    MU_RUN_SUITE(to_bignum_tests);
    MU_RUN_SUITE(to_str_tests);
    MU_REPORT();
    return MU_EXIT_CODE;
}
