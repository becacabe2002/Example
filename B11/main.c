#include <stdio.h>
#include "cgen.h"
int main() {
  int a, b;
  hmap_t map = hmap_create(gtype_hash_s, gtype_cmp_s, NULL, NULL);
  hmap_free(map);
  return 0;