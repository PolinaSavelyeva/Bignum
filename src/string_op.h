#pragma once

#include "bignum.h"

bignum_t *to_bignum(char *str);
char *to_str(bignum_t *bignum);