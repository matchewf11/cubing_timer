#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cli/cli.h"
#include "db/db.h"
#include "scramble/scramble.h"
#include "timer/timer.h"

int cli_run();
int cli_stats();

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
    return cli_stats();
  case CLI_RUN:
    return cli_run();
  }
}

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
  printf("\nTime: %.3f\n", time);

  sqlite3 *db;
  if (init_db(&db) != SQLITE_OK) {
    free(moves);
    return 1;
  }

  if (init_tables(db) != SQLITE_OK ||
      insert_solve(db, time, moves, len) != SQLITE_OK) {
    sqlite3_close(db);
    free(moves);
    return 1;
  }

  sqlite3_close(db);
  free(moves);
  return 0;
}

int cli_stats() {

  sqlite3 *db;
  if (init_db(&db) != SQLITE_OK) {
    return 1;
  }

  double avg;
  if (get_avg_all_time(db, &avg) != SQLITE_OK) {
    sqlite3_close(db);
    return 1;
  }

  printf("All Time Avg: %.3f\n", avg);

  sqlite3_close(db);
  return 0;
}
