#include <stdio.h>
#include <string.h>

#include "../scramble/scramble.h"
#include "cube_display.h"

const int up = 0;
const int left = 1;
const int front = 2;
const int right = 3;
const int back = 4;
const int down = 5;

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

static void rotate_face_cw(CubeColor face[9]) {
  CubeColor temp = face[0];
  face[0] = face[6];
  face[6] = face[8];
  face[8] = face[2];
  face[2] = temp;
  temp = face[1];
  face[1] = face[3];
  face[3] = face[7];
  face[7] = face[5];
  face[5] = temp;
}

static void f_move(Cube cube) {

  rotate_face_cw(cube[front]);

  CubeColor temp[3] = {cube[up][6], cube[up][7], cube[up][8]};

  cube[up][6] = cube[left][8];
  cube[up][7] = cube[left][5];
  cube[up][8] = cube[left][2];

  cube[left][8] = cube[down][2];
  cube[left][5] = cube[down][1];
  cube[left][2] = cube[down][0];

  cube[down][2] = cube[right][0];
  cube[down][1] = cube[right][3];
  cube[down][0] = cube[right][6];

  cube[right][0] = temp[0];
  cube[right][3] = temp[1];
  cube[right][6] = temp[2];
}

static void b_move(Cube cube) {

  rotate_face_cw(cube[back]);

  for (int i = 0; i < 3; i++) {
    CubeColor temp = cube[up][i];
    cube[up][i] = cube[right][2 + (i * 3)];
    cube[right][2 + (i * 3)] = cube[down][8 - i];
    cube[down][8 - i] = cube[left][6 - (i * 3)];
    cube[left][6 - (i * 3)] = temp;
  }
}

static void r_move(Cube cube) {

  rotate_face_cw(cube[right]);

  for (int i = 0; i < 3; i++) {
    CubeColor temp = cube[up][2 + i * 3];
    cube[up][2 + i * 3] = cube[front][2 + i * 3];
    cube[front][2 + i * 3] = cube[down][2 + i * 3];
    cube[down][2 + i * 3] = cube[back][6 - i * 3];
    cube[back][6 - i * 3] = temp;
  }
}

static void l_move(Cube cube) {

  rotate_face_cw(cube[left]);

  for (int i = 0; i < 3; i++) {
    CubeColor temp = cube[up][i * 3];
    cube[up][i * 3] = cube[back][8 - i * 3];
    cube[back][8 - i * 3] = cube[down][i * 3];
    cube[down][i * 3] = cube[front][i * 3];
    cube[front][i * 3] = temp;
  }
}

static void u_move(Cube cube) {

  rotate_face_cw(cube[up]);

  for (int i = 0; i < 3; i++) {
    CubeColor temp = cube[front][i];
    cube[front][i] = cube[right][i];
    cube[right][i] = cube[back][i];
    cube[back][i] = cube[left][i];
    cube[left][i] = temp;
  }
}

static void d_move(Cube cube) {

  rotate_face_cw(cube[down]);

  for (int i = 6; i < 9; i++) {
    CubeColor temp = cube[front][i];
    cube[front][i] = cube[left][i];
    cube[left][i] = cube[back][i];
    cube[back][i] = cube[right][i];
    cube[right][i] = temp;
  }
}

void display_scrambled_cube(Cube cube) {
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

void scramble_cube(Cube cube, const CubeMove *moves, int len) {
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
}
