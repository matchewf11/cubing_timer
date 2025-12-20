#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../scramble/scramble.h"
#include "../term/term.h"

static inline void print_moves(CubeMove *const moves, int len) {
  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(moves[i]));
  }
  printf("\n");
}

int start_cube_timer() {

  struct timespec start, end;

  int len;
  CubeMove *moves = generate_scramble(&len);
  if (moves == NULL) {
    return -1;
  }

  clear_term();

  print_moves(moves, len);
  printf("Press <Space> to Start & Stop\n");

  if (enable_raw_mode() == -1) {
    free(moves);
    return -1;
  }

  // only move forward when space is pressed
  while (1) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1) {
      free(moves);
      return -1;
    }
    if (c == ' ') {
      break;
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &start);

  // now print timer over and over again
  // until another space is pressed
  while (1) {
    clock_gettime(CLOCK_MONOTONIC, &end);
    double curr_time =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    clear_term();
    printf("%.3f\n", curr_time);

    // break if a space is hit
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1) {
      free(moves);
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
  free(moves);
  return 0;
}
