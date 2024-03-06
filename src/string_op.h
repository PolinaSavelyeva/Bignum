#include "bignum.h"
#ifndef STRING_OP_H
#define STRING_OP_H

bignum_t *to_bignum(char *str);
char *to_str(bignum_t *bignum);

#endif /* STRING_OP_H */