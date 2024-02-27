#include "minunit.h"
#include "math_op.h"
#include "helper.h"
#include "string_op.h"
#include <stdlib.h>
#include "string_op.h"

MU_TEST(add_negative_same_length)
{
    bignum_t *fst = init_bignum_mods(1, 5);
    bignum_t *snd = init_bignum_mods(1, 5);
    unsigned int *res_digits = malloc(5 * sizeof(unsigned int));
    res_digits[0] = 0;
    res_digits[1] = 9;
    res_digits[2] = 6;
    res_digits[3] = 4;
    res_digits[4] = 2;

    bignum_t *res = init_bignum_digits(1, res_digits, 5);
    bignum_t *add_res = add(fst, snd);

    mu_check(is_equal(add(fst, snd), res));

    free_bignum(fst);
    free_bignum(snd);
    free_bignum(res);
    free_bignum(add_res);
}

MU_TEST(add_positive_same_length)
{
    bignum_t *fst = init_bignum_mods(0, 15);
    bignum_t *snd = init_bignum_mods(0, 15);
    bignum_t *res = to_bignum("246913578024690");
    bignum_t *add_res = add(fst, snd);

    mu_check(is_equal(add(fst, snd), res));

    free_bignum(fst);
    free_bignum(snd);
    free_bignum(res);
    free_bignum(add_res);
}

MU_TEST(add_negative)
{
    bignum_t *fst = to_bignum("-12345");
    bignum_t *snd = to_bignum("-54321");
    bignum_t *res = to_bignum("-66666");
    bignum_t *add_res = add(fst, snd);

    mu_check(is_equal(add_res, res));

    free_bignum(fst);
    free_bignum(snd);
    free_bignum(res);
    free_bignum(add_res);
}

MU_TEST(add_positive)
{
    bignum_t *fst = to_bignum("12345");
    bignum_t *snd = to_bignum("54321");
    bignum_t *res = to_bignum("66666");
    bignum_t *add_res = add(fst, snd);

    mu_check(is_equal(add_res, res));

    free_bignum(fst);
    free_bignum(snd);
    free_bignum(res);
    free_bignum(add_res);
}

MU_TEST_SUITE(add_tests)
{
    MU_RUN_TEST(add_negative_same_length);
    MU_RUN_TEST(add_positive_same_length);
    MU_RUN_TEST(add_positive);
    MU_RUN_TEST(add_negative);
}

int main()
{
    MU_RUN_SUITE(add_tests);
    MU_REPORT();
    return MU_EXIT_CODE;
}
