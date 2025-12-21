#include <stdlib.h>
#include <string.h>

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

const char *cube_move_str(CubeMove move) {
  switch (move) {
  case MOVE_RIGHT:
    return "R";
  case MOVE_LEFT:
    return "L";
  case MOVE_UP:
    return "U";
  case MOVE_DOWN:
    return "D";
  case MOVE_FRONT:
    return "F";
  case MOVE_BACK:
    return "B";
  case MOVE_RIGHT_P:
    return "R'";
  case MOVE_LEFT_P:
    return "L'";
  case MOVE_UP_P:
    return "U'";
  case MOVE_DOWN_P:
    return "D'";
  case MOVE_FRONT_P:
    return "F'";
  case MOVE_BACK_P:
    return "B'";
  case MOVE_RIGHT_2:
    return "R2";
  case MOVE_LEFT_2:
    return "L2";
  case MOVE_UP_2:
    return "U2";
  case MOVE_DOWN_2:
    return "D2";
  case MOVE_FRONT_2:
    return "F2";
  case MOVE_BACK_2:
    return "B2";
  }
}

char *scramble_to_string(const CubeMove *moves, int len) {
  // make size for move is 2
  // add 1 for null terminator
  char *str = malloc(sizeof(char) * (len * 3 + 1));
  if (str == NULL) {
    return NULL;
  }

  int str_i = 0;
  for (int i = 0; i < len; i++) {

    if (i > 0) {
      str[str_i++] = ' ';
    }

    const char *curr_move_str = cube_move_str(moves[i]);
    const int curr_len = strlen(curr_move_str);


    strncpy(&str[str_i], curr_move_str, curr_len);
    str_i += curr_len;
  }

  str[str_i] = '\0';

  return str;
}
