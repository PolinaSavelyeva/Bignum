#pragma once

#include "bignum.h"

bignum_t *str_to_bignum(char *str);
char *bignum_to_str(bignum_t *bignum);