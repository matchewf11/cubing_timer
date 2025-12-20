#include <stdlib.h>

#include "scramble.h"

static CubeMove get_rand_move() {
  return (CubeMove)(rand() % 17); // only works if cube move does not change
}

CubeMove *generate_scramble(int *out) {

  const int len = 30;

  CubeMove *list = malloc(sizeof(CubeMove) * len);
  if (list == NULL) {
    *out = 0;
    return NULL;
  }

  *out = len;

  for (int i = 0; i < len; i++) {
    list[i] = get_rand_move();
  }

  return list;
}
