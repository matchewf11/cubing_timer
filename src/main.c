#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cli/cli.h"
#include "timer/timer.h"

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
    start_cube_timer();
    return 0;
  }
}
