#include <stdio.h>

typedef enum { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE } CubeColor;

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

void display_cube() {
  CubeColor cube[6][9] = {
      {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE},
      {ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE},
      {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
      {RED, RED, RED, RED, RED, RED, RED, RED, RED},
      {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE},
      {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW},
  };

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
