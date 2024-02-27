#include "minunit.h"
#include "string_op.h"
#include "tests.h"
#include <stdlib.h>
#include <stdio.h>

static bignum_t *bignum;
static unsigned int *digits;

static void init_bignum(bool sign, unsigned int length)
{
    digits = malloc(length * sizeof(unsigned int));
    bignum = malloc(sizeof(bignum_t));

    bignum->sign = sign;
    bignum->length = length;
    bignum->digits = digits;

    for (int i = 0; i < length; i++)
    {
        digits[length - i - 1] = (i + 1) % 10;
    }
}

static bool is_equal(bignum_t *bignum_fst, bignum_t *bignum_snd)
{
    return (bignum_fst->sign == bignum_snd->sign &&
            bignum_fst->length == bignum_snd->length &&
            !memcmp(bignum_fst->digits, bignum_snd->digits, sizeof(bignum_fst->digits)));
}

MU_TEST(to_bignum_small_negative)
{
    init_bignum(1, 3);
    mu_check(is_equal(bignum, to_bignum("-123")));
    free(bignum);
    free(digits);
}

MU_TEST(to_bignum_small_positive_unsigned)
{
    init_bignum(0, 7);
    mu_check(is_equal(bignum, to_bignum("1234567")));
    free(bignum);
    free(digits);
}

MU_TEST(to_bignum_small_positive_signed)
{
    init_bignum(0, 7);
    mu_check(is_equal(bignum, to_bignum("+1234567")));
    free(bignum);
    free(digits);
}

MU_TEST(to_bignum_big_negative)
{
    init_bignum(1, 15);
    mu_check(is_equal(bignum, to_bignum("-123456789012345")));
    free(bignum);
    free(digits);
}

MU_TEST(to_bignum_big_positive)
{
    init_bignum(0, 10);
    mu_check(is_equal(bignum, to_bignum("1234567890")));
    free(bignum);
    free(digits);
}

MU_TEST_SUITE(to_bignum_tests)
{
    MU_RUN_TEST(to_bignum_small_negative);
    MU_RUN_TEST(to_bignum_small_positive_unsigned);
    MU_RUN_TEST(to_bignum_small_positive_signed);
    MU_RUN_TEST(to_bignum_big_negative);
    MU_RUN_TEST(to_bignum_big_positive);
}

MU_TEST(to_str_small_negative)
{
    init_bignum(1, 3);
    mu_assert_string_eq(to_str(bignum), "-123");
    free(bignum);
    free(digits);
}

MU_TEST(to_str_small_positive)
{
    init_bignum(0, 7);
    mu_assert_string_eq(to_str(bignum), "1234567");
    free(bignum);
    free(digits);
}

MU_TEST(to_str_big_negative)
{
    init_bignum(1, 15);
    mu_assert_string_eq(to_str(bignum), "-123456789012345");
    free(bignum);
    free(digits);
}

MU_TEST(to_str_big_positive)
{
    init_bignum(0, 10);
    mu_assert_string_eq(to_str(bignum), "1234567890");
    free(bignum);
    free(digits);
}

MU_TEST_SUITE(to_str_tests)
{
    MU_RUN_TEST(to_str_small_negative);
    MU_RUN_TEST(to_str_small_positive);
    MU_RUN_TEST(to_str_big_negative);
    MU_RUN_TEST(to_str_big_positive);
}

int run_string_tests()
{
    MU_RUN_SUITE(to_bignum_tests);
    MU_RUN_SUITE(to_str_tests);
    MU_REPORT();
    return MU_EXIT_CODE;
}
