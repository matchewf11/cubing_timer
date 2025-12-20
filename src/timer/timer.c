#include <stdio.h>
#include <stdlib.h>
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
  int len;
  CubeMove *moves = generate_scramble(&len);
  if (moves == NULL) {
    return -1;
  }

  clear_term();

  print_moves(moves, len);
  printf("Press <Space> to Start\n");

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

  if (disable_raw_mode() == -1) {
    free(moves);
    return -1;
  }

  // now print timer over and over again

  free(moves);
  return 0;
}
