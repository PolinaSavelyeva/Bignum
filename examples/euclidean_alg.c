#include "euclidean_alg.h"

#include "math_op.h"

bignum_t *euclidean_alg(bignum_t *fst, bignum_t *snd) {
  if (!bignum_cmp_abs(fst, snd)) return euclidean_alg(snd, fst);

  bignum_t *tmp_fst = bignum_copy(fst);
  bignum_t *tmp_snd = bignum_copy(snd);

  bignum_t *mod_res;
  do {
    mod_res = bignum_mod(tmp_fst, tmp_snd);
    free_bignum(tmp_fst);
    tmp_fst = tmp_snd;
    tmp_snd = mod_res;
  } while (mod_res->sign);

  free_bignum(tmp_snd);

  return tmp_fst;
}