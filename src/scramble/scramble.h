#ifndef SCRAMBLE_H
#define SCRAMBLE_H

typedef enum {
  MOVE_RIGHT,
  MOVE_LEFT,
  MOVE_UP,
  MOVE_DOWN,
  MOVE_FRONT,
  MOVE_BACK,
  MOVE_RIGHT_P,
  MOVE_LEFT_P,
  MOVE_UP_P,
  MOVE_DOWN_P,
  MOVE_FRONT_P,
  MOVE_BACK_P,
  MOVE_RIGHT_2,
  MOVE_LEFT_2,
  MOVE_UP_2,
  MOVE_DOWN_2,
  MOVE_FRONT_2,
  MOVE_BACK_2,
} CubeMove;

// Check if output is null
// free when done with it
// out is the len of the array
CubeMove *generate_scramble(int *out);

// Returns static string
// representation of enum
const char *cube_move_str(CubeMove move);

#endif
