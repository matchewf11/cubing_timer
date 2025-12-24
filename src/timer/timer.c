#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../cube_display/cube_display.h"
#include "../scramble/scramble.h"
#include "../term/term.h"

int start_cube_timer(double *out_time, CubeMove **out_moves,
                     int *out_moves_len) {
  struct timespec start, end;

  int len;
  CubeMove *moves = generate_scramble(&len);
  if (moves == NULL) {
    return -1;
  }

  clear_term();

  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(moves[i]));
  }
  printf("\n");

  printf("Press <Space> to Start & Stop\n");

  Cube cube;
  memcpy(cube, DEFAULT_CUBE, sizeof(DEFAULT_CUBE));
  scramble_cube(cube, moves, len);
  display_scrambled_cube(cube);

  if (enable_raw_mode() == -1) {
    free(moves);
    return -1;
  }

  // only move forward when space is pressed
  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1) {
      disable_raw_mode();
      free(moves);
      return -1;
    }
    if (c == ' ') {
      break;
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &start);
  double curr_time;

  // now print timer over and over again
  // until another space is pressed
  while (1) {
    clock_gettime(CLOCK_MONOTONIC, &end);
    curr_time =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    clear_term();
    printf("%.3f\n", curr_time);

    // break if a space is hit
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1) {
      free(moves);
      disable_raw_mode();
      return -1;
    }
    if (c == ' ') {
      break;
    }

    // sleep a little to reduce cpu usage
    // sleeps for 0.0005 seconds
    usleep(500);
  }

  if (disable_raw_mode() == -1) {
    free(moves);
    return -1;
  }

  clear_term();

  *out_moves = moves;
  *out_time = curr_time;
  *out_moves_len = len;
  return 0;
}
