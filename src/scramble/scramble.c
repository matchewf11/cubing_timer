#include <stdlib.h>
#include <string.h>

#include "scramble.h"

typedef enum { FACE_F, FACE_B, FACE_R, FACE_L, FACE_U, FACE_D } CubeFace;

typedef struct {
  CubeFace face;
  int turns; // 1 = cw, 2 = _2, 3 = cc
} MoveInfo;

static MoveInfo move_info(CubeMove m) {
  switch (m) {
  case MOVE_RIGHT:
    return (MoveInfo){FACE_R, 1};
  case MOVE_RIGHT_P:
    return (MoveInfo){FACE_R, 3};
  case MOVE_RIGHT_2:
    return (MoveInfo){FACE_R, 2};
  case MOVE_LEFT:
    return (MoveInfo){FACE_L, 1};
  case MOVE_LEFT_P:
    return (MoveInfo){FACE_L, 3};
  case MOVE_LEFT_2:
    return (MoveInfo){FACE_L, 2};
  case MOVE_UP:
    return (MoveInfo){FACE_U, 1};
  case MOVE_UP_P:
    return (MoveInfo){FACE_U, 3};
  case MOVE_UP_2:
    return (MoveInfo){FACE_U, 2};
  case MOVE_DOWN:
    return (MoveInfo){FACE_D, 1};
  case MOVE_DOWN_P:
    return (MoveInfo){FACE_D, 3};
  case MOVE_DOWN_2:
    return (MoveInfo){FACE_D, 2};
  case MOVE_FRONT:
    return (MoveInfo){FACE_F, 1};
  case MOVE_FRONT_P:
    return (MoveInfo){FACE_F, 3};
  case MOVE_FRONT_2:
    return (MoveInfo){FACE_F, 2};
  case MOVE_BACK:
    return (MoveInfo){FACE_B, 1};
  case MOVE_BACK_P:
    return (MoveInfo){FACE_B, 3};
  case MOVE_BACK_2:
    return (MoveInfo){FACE_B, 2};
  }
}

// not needed if turns is 0
static CubeMove move_from(CubeFace face, int turns) {
  turns %= 4;
  switch (face) {
  case FACE_R:
    return turns == 1 ? MOVE_RIGHT : turns == 2 ? MOVE_RIGHT_2 : MOVE_RIGHT_P;
  case FACE_L:
    return turns == 1 ? MOVE_LEFT : turns == 2 ? MOVE_LEFT_2 : MOVE_LEFT_P;
  case FACE_U:
    return turns == 1 ? MOVE_UP : turns == 2 ? MOVE_UP_2 : MOVE_UP_P;
  case FACE_D:
    return turns == 1 ? MOVE_DOWN : turns == 2 ? MOVE_DOWN_2 : MOVE_DOWN_P;
  case FACE_F:
    return turns == 1 ? MOVE_FRONT : turns == 2 ? MOVE_FRONT_2 : MOVE_FRONT_P;
  case FACE_B:
    return turns == 1 ? MOVE_BACK : turns == 2 ? MOVE_BACK_2 : MOVE_BACK_P;
  }
}

// remove duplicate elements
// return new len
static int simplify_scramble(CubeMove *moves, int len) {
  for (int i = 0; i < len - 1;) {
    MoveInfo a = move_info(moves[i]);
    MoveInfo b = move_info(moves[i + 1]);

    if (a.face != b.face) {
      i++;
      continue;
    }

    int turns = (a.turns + b.turns) % 4;

    if (turns == 0) {
      memmove(&moves[i], &moves[i + 2], sizeof(CubeMove) * (len - i - 2));
      len -= 2;
      if (i > 0) {
        i--;
      }
    } else {
      moves[i] = move_from(a.face, turns);
      memmove(&moves[i + 1], &moves[i + 2], sizeof(CubeMove) * (len - i - 2));
      len -= 1;
      if (i > 0) {
        i--;
      }
    }
  }

  return len;
}

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
  for (int i = 0; i < len; i++) {
    list[i] = get_rand_move();
  }

  *out = simplify_scramble(list, len);

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
