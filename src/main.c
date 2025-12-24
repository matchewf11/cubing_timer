#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cli/cli.h"
#include "cube_display/cube_display.h"
#include "db/db.h"
#include "scramble/scramble.h"
#include "term/term.h"
#include "timer/timer.h"

int cli_run();
int cli_stats();
int cli_delete();
int cli_plus_two();
int cli_typing();
int cli_virtual();
int cli_gen_scram();

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));

  CliCmd cmd = parse_args((const char **)argv, argc);
  switch (cmd) {
  case CLI_INVALID:
    printf("Invlaid Command: try running the help cmd\n");
    return -1;
  case CLI_HELP:
    printf("Commands: help, stats, run\nhelp: information\nstats: prints some "
           "stats (personal best, all time count/avg, last 5 solves)\nrun: "
           "starts solve\ndelete: delete the last solve\nplus2: adds 2 to the "
           "last solve\ntyping: allows for manually typing timer\nvirtual: "
           "virtual cube solver\ngenscram: generates scramble\n");
    return 0;
  case CLI_STATS:
    return cli_stats();
  case CLI_RUN:
    return cli_run();
  case CLI_DELETE:
    return cli_delete();
  case CLI_PLUS_TWO:
    return cli_plus_two();
  case CLI_TYPING:
    return cli_typing();
  case CLI_VIRTUAL:
    return cli_virtual();
  case CLI_GEN_SCRAM:
    return cli_gen_scram();
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
  int count;
  if (get_avg_all_time(db, &avg, &count) != SQLITE_OK) {
    sqlite3_close(db);
    return 1;
  }

  double pb;
  char *scramble_str;

  if (get_personal_best(db, &pb, &scramble_str) != SQLITE_OK) {
    sqlite3_close(db);
    return 1;
  }

  double *times;
  char **scrambles;
  int scramble_len;
  if (get_curr_5(db, &times, &scrambles, &scramble_len) != SQLITE_OK) {
    sqlite3_close(db);
    free(scramble_str);
    return -1;
  }

  printf("Last %d Scrambles:\n", scramble_len);
  for (int i = 0; i < scramble_len; i++) {
    printf("Time: %.3f - %s\n", times[i], scrambles[i]);
  }
  printf("\n");

  printf("All Time Avg: %.3f\n", avg);
  printf("All Time Count: %d\n", count);
  printf("Personal Best: %.3f: %s\n", pb, scramble_str);

  sqlite3_close(db);

  for (int i = 0; i < scramble_len; i++) {
    free(scrambles[i]);
  }

  free(times);
  free(scrambles);
  free(scramble_str);
  return 0;
}

int cli_delete() {
  sqlite3 *db;
  if (init_db(&db) != SQLITE_OK) {
    return 1;
  }

  if (delete_last_solve(db) != SQLITE_OK) {
    sqlite3_close(db);
    return 1;
  }

  printf("Deleted Last Solve\n");
  sqlite3_close(db);
  return 0;
}

int cli_plus_two() {
  sqlite3 *db;
  if (init_db(&db) != SQLITE_OK) {
    return 1;
  }

  int rs = add_two_last_scramble(db);
  sqlite3_close(db);
  printf("Adding 2 to last time\n");
  return rs == SQLITE_OK ? 0 : 1;
}

int cli_typing() {
  int len;
  CubeMove *moves = generate_scramble(&len);
  if (moves == NULL) {
    return 1;
  }

  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(moves[i]));
  }
  printf("\n");

  Cube cube;
  memcpy(cube, DEFAULT_CUBE, sizeof(DEFAULT_CUBE));
  scramble_cube(cube, moves, len);
  display_scrambled_cube(cube);

  printf("Insert Time Below:\n");

  double input;

  if (scanf("%lf", &input) < 1) {
    free(moves);
    return 1;
  }

  sqlite3 *db;
  if (init_db(&db) != SQLITE_OK) {
    free(moves);
    return 1;
  }

  if (init_tables(db) != SQLITE_OK ||
      insert_solve(db, input, moves, len) != SQLITE_OK) {
    sqlite3_close(db);
    free(moves);
    return 1;
  }

  sqlite3_close(db);
  free(moves);
  return 0;
}

int cli_virtual() {
  int len;
  CubeMove *moves = generate_scramble(&len);
  if (moves == NULL) {
    return 1;
  }

  struct timespec start, end;

  Cube cube;
  memcpy(cube, DEFAULT_CUBE, sizeof(DEFAULT_CUBE));

  scramble_cube(cube, moves, len);

  if (enable_raw_virtual() != 0) {
    free(moves);
    return 1;
  }

  int have_moved = 0;
  double curr_time = 0.0;

  while (!cube_solved(cube)) {

    clear_term();
    display_scrambled_cube(cube);
    printf("%.3f\n\n", curr_time);
    printf("f: front\nb: back\nl: left\nr: right\nu: up\nd: down\n");

    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) == -1) {
      disable_raw_mode();
      free(moves);
      return 1;
    }

    int inner_have_moved = 0;
    switch (c) {
    case 'f':
      f_move(cube);
      inner_have_moved = 1;
      break;
    case 'b':
      b_move(cube);
      inner_have_moved = 1;
      break;
    case 'u':
      u_move(cube);
      inner_have_moved = 1;
      break;
    case 'd':
      d_move(cube);
      inner_have_moved = 1;
      break;
    case 'r':
      r_move(cube);
      inner_have_moved = 1;
      break;
    case 'l':
      l_move(cube);
      inner_have_moved = 1;
      break;
    default:
      break;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    if (!have_moved) {
      start = end;
    }
    curr_time =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    if (inner_have_moved) {
      have_moved = 1;
    }
  }

  if (disable_raw_mode() != 0) {
    free(moves);
    return 1;
  }

  clear_term();

  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(moves[i]));
  }
  printf("\nTime: %.3f\n", curr_time);

  // insert into the db
  sqlite3 *db;
  if (init_db(&db) != SQLITE_OK) {
    free(moves);
    return 1;
  }

  if (init_tables(db) != SQLITE_OK ||
      insert_solve(db, curr_time, moves, len) != SQLITE_OK) {

    sqlite3_close(db);
    free(moves);
    return 1;
  }

  sqlite3_close(db);
  free(moves);
  return 0;
}

int cli_gen_scram() {
  int len;
  CubeMove *moves = generate_scramble(&len);
  if (moves == NULL) {
    return 1;
  }

  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(moves[i]));
  }
  printf("\n");

  free(moves);
  return 0;
}
