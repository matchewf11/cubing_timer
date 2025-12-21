#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cli/cli.h"
#include "scramble/scramble.h"
#include "timer/timer.h"

// return 0 or 1 as exit code
int cli_run() {
  double time;
  CubeMove *moves;
  int len;

  int results = start_cube_timer(&time, &moves, &len);
  if (results == -1) {
    return 1;
  }

  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(moves[i]));
  }
  printf("\n%f\n", time);

  free(moves);
  return 0;
}

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));

  CliCmd cmd = parse_args((const char **)argv, argc);
  switch (cmd) {
  case CLI_INVALID:
    printf("Invlaid: help, stats, and run are the valid cmds.\n");
    return -1;
  case CLI_HELP:
    printf("Commands: help, stats, run\nhelp: information\nstats: prints some "
           "stats\nrun: starts solve\n");
    return 0;
  case CLI_STATS:
    printf("TODO\n");
    return 0;
  case CLI_RUN:
    return cli_run();
  }
}
