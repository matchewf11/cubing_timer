#include <stdio.h>

#include "../scramble/scramble.h"

typedef enum { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE } CubeColor;

typedef CubeColor Cube[6][9];

static void display_square(CubeColor color) {
  switch (color) {
  case WHITE:
    printf("\033[47m  \033[0m");
    break;
  case YELLOW:
    printf("\033[43m  \033[0m");
    break;
  case BLUE:
    printf("\033[44m  \033[0m");
    break;
  case GREEN:
    printf("\033[42m  \033[0m");
    break;
  case RED:
    printf("\033[41m  \033[0m");
    break;
  case ORANGE:
    printf("\033[48;5;208m  \033[0m");
    break;
  }
}

// static void f_move(Cube cube) {
//   enum { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
//
//   CubeColor temp_row[3] = {cube[U][6], cube[U][7], cube[U][8]};
//   CubeColor temp = cube[F][0];
//
//   cube[F][0] = cube[F][6];
//   cube[F][6] = cube[F][8];
//   cube[F][8] = cube[F][2];
//   cube[F][2] = temp;
//
//   temp = cube[F][1];
//   cube[F][1] = cube[F][3];
//   cube[F][3] = cube[F][7];
//   cube[F][7] = cube[F][5];
//   cube[F][5] = temp;
//
//   cube[U][6] = cube[L][8];
//   cube[U][7] = cube[L][5];
//   cube[U][8] = cube[L][2];
//
//   cube[L][8] = cube[D][2];
//   cube[L][5] = cube[D][1];
//   cube[L][2] = cube[D][0];
//
//   cube[D][2] = cube[R][0];
//   cube[D][1] = cube[R][3];
//   cube[D][0] = cube[R][6];
//
//   cube[R][0] = temp_row[0];
//   cube[R][3] = temp_row[1];
//   cube[R][6] = temp_row[2];
// }
//
// static void b_move(CubeColor cube[6][9]) {
//   enum { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
//
//   CubeColor temp_row[3] = {cube[U][0], cube[U][1], cube[U][2]};
//
//   CubeColor temp = cube[B][0];
//
//   cube[B][0] = cube[B][6];
//   cube[B][6] = cube[B][8];
//   cube[B][8] = cube[B][2];
//   cube[B][2] = temp;
//
//   temp = cube[B][1];
//   cube[B][1] = cube[B][3];
//   cube[B][3] = cube[B][7];
//   cube[B][7] = cube[B][5];
//   cube[B][5] = temp;
//
//   cube[U][0] = cube[R][2];
//   cube[U][1] = cube[R][5];
//   cube[U][2] = cube[R][8];
//
//   cube[R][2] = cube[D][8];
//   cube[R][5] = cube[D][7];
//   cube[R][8] = cube[D][6];
//
//   cube[D][8] = cube[L][0];
//   cube[D][7] = cube[L][3];
//   cube[D][6] = cube[L][6];
//
//   cube[L][0] = temp_row[2];
//   cube[L][3] = temp_row[1];
//   cube[L][6] = temp_row[0];
// }
//
// static void l_move(CubeColor cube[6][9]) {
//   enum { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
//
//   CubeColor temp_col[3] = {cube[U][0], cube[U][3], cube[U][6]};
//
//   CubeColor temp = cube[L][0];
//
//   cube[L][0] = cube[L][6];
//   cube[L][6] = cube[L][8];
//   cube[L][8] = cube[L][2];
//   cube[L][2] = temp;
//
//   temp = cube[L][1];
//   cube[L][1] = cube[L][3];
//   cube[L][3] = cube[L][7];
//   cube[L][7] = cube[L][5];
//   cube[L][5] = temp;
//
//   cube[U][0] = cube[B][8];
//   cube[U][3] = cube[B][5];
//   cube[U][6] = cube[B][2];
//
//   cube[B][8] = cube[D][6];
//   cube[B][5] = cube[D][3];
//   cube[B][2] = cube[D][0];
//
//   cube[D][6] = cube[F][6];
//   cube[D][3] = cube[F][3];
//   cube[D][0] = cube[F][0];
//
//   cube[F][0] = temp_col[0];
//   cube[F][3] = temp_col[1];
//   cube[F][6] = temp_col[2];
// }
//
// static void r_move(CubeColor cube[6][9]) {
//   enum { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
//
//   CubeColor temp_col[3] = {cube[U][2], cube[U][5], cube[U][8]};
//
//   CubeColor temp = cube[R][0];
//
//   cube[R][0] = cube[R][6];
//   cube[R][6] = cube[R][8];
//   cube[R][8] = cube[R][2];
//   cube[R][2] = temp;
//
//   temp = cube[R][1];
//   cube[R][1] = cube[R][3];
//   cube[R][3] = cube[R][7];
//   cube[R][7] = cube[R][5];
//   cube[R][5] = temp;
//
//   cube[U][2] = cube[F][2];
//   cube[U][5] = cube[F][5];
//   cube[U][8] = cube[F][8];
//
//   cube[F][2] = cube[D][2];
//   cube[F][5] = cube[D][5];
//   cube[F][8] = cube[D][8];
//
//   cube[D][2] = cube[B][6];
//   cube[D][5] = cube[B][3];
//   cube[D][8] = cube[B][0];
//
//   cube[B][6] = temp_col[0];
//   cube[B][3] = temp_col[1];
//   cube[B][0] = temp_col[2];
// }
//
// static void u_move(CubeColor cube[6][9]) {
//   enum { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
//
//   CubeColor tmp[3] = {cube[B][0], cube[B][1], cube[B][2]};
//
//   CubeColor t = cube[U][0];
//   cube[U][0] = cube[U][6];
//   cube[U][6] = cube[U][8];
//   cube[U][8] = cube[U][2];
//   cube[U][2] = t;
//   t = cube[U][1];
//   cube[U][1] = cube[U][3];
//   cube[U][3] = cube[U][7];
//   cube[U][7] = cube[U][5];
//   cube[U][5] = t;
//
//   cube[B][0] = cube[L][0];
//   cube[B][1] = cube[L][1];
//   cube[B][2] = cube[L][2];
//   cube[L][0] = cube[F][0];
//   cube[L][1] = cube[F][1];
//   cube[L][2] = cube[F][2];
//   cube[F][0] = cube[R][0];
//   cube[F][1] = cube[R][1];
//   cube[F][2] = cube[R][2];
//   cube[R][0] = tmp[0];
//   cube[R][1] = tmp[1];
//   cube[R][2] = tmp[2];
// }
//
// static void d_move(CubeColor cube[6][9]) {
//   enum { U = 0, L = 1, F = 2, R = 3, B = 4, D = 5 };
//
//   CubeColor tmp[3] = {cube[F][6], cube[F][7], cube[F][8]};
//
//   CubeColor temp = cube[D][0];
//   cube[D][0] = cube[D][6];
//   cube[D][6] = cube[D][8];
//   cube[D][8] = cube[D][2];
//   cube[D][2] = temp;
//   temp = cube[D][1];
//   cube[D][1] = cube[D][3];
//   cube[D][3] = cube[D][7];
//   cube[D][7] = cube[D][5];
//   cube[D][5] = temp;
//
//   cube[F][6] = cube[L][6];
//   cube[F][7] = cube[L][7];
//   cube[F][8] = cube[L][8];
//   cube[L][6] = cube[B][8];
//   cube[L][7] = cube[B][7];
//   cube[L][8] = cube[B][6];
//   cube[B][6] = cube[R][6];
//   cube[B][7] = cube[R][7];
//   cube[B][8] = cube[R][8];
//   cube[R][6] = tmp[0];
//   cube[R][7] = tmp[1];
//   cube[R][8] = tmp[2];
// }

void display_cube(const CubeMove *moves, int len) {
  Cube cube = {
      {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE},
      {ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE},
      {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
      {RED, RED, RED, RED, RED, RED, RED, RED, RED},
      {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE},
      {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW},
  };

  for (int i = 0; i < len; i++) {
    switch (moves[i]) {
    case MOVE_FRONT:
      f_move(cube);
      break;
    case MOVE_FRONT_P:
      f_move(cube);
      f_move(cube);
      f_move(cube);
      break;
    case MOVE_FRONT_2:
      f_move(cube);
      f_move(cube);
      break;

    case MOVE_BACK:
      b_move(cube);
      break;
    case MOVE_BACK_P:
      b_move(cube);
      b_move(cube);
      b_move(cube);
      break;
    case MOVE_BACK_2:
      b_move(cube);
      b_move(cube);
      break;

    case MOVE_UP:
      u_move(cube);
      break;
    case MOVE_UP_P:
      u_move(cube);
      u_move(cube);
      u_move(cube);
      break;
    case MOVE_UP_2:
      u_move(cube);
      u_move(cube);
      break;

    case MOVE_DOWN:
      d_move(cube);
      break;
    case MOVE_DOWN_P:
      d_move(cube);
      d_move(cube);
      d_move(cube);
      break;
    case MOVE_DOWN_2:
      d_move(cube);
      d_move(cube);
      break;

    case MOVE_LEFT:
      l_move(cube);
      break;
    case MOVE_LEFT_P:
      l_move(cube);
      l_move(cube);
      l_move(cube);
      break;
    case MOVE_LEFT_2:
      l_move(cube);
      l_move(cube);
      break;

    case MOVE_RIGHT:
      r_move(cube);
      break;
    case MOVE_RIGHT_P:
      r_move(cube);
      r_move(cube);
      r_move(cube);
      break;
    case MOVE_RIGHT_2:
      r_move(cube);
      r_move(cube);
      break;
    }
  }

  for (int i = 0; i < 3; i++) {
    printf("      ");
    display_square(cube[0][0 + i * 3]);
    display_square(cube[0][1 + i * 3]);
    display_square(cube[0][2 + i * 3]);
    printf("\n");
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 1; j < 5; j++) {
      display_square(cube[j][0 + i * 3]);
      display_square(cube[j][1 + i * 3]);
      display_square(cube[j][2 + i * 3]);
    }
    printf("\n");
  }

  for (int i = 0; i < 3; i++) {
    printf("      ");
    display_square(cube[5][0 + i * 3]);
    display_square(cube[5][1 + i * 3]);
    display_square(cube[5][2 + i * 3]);
    printf("\n");
  }
}
