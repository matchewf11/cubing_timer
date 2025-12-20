#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cli/cli.h"
#include "scramble/scramble.h"

int main(int argc, char *argv[]) {
  srand((unsigned)time(NULL));

  CliCmd cmd = parse_args((const char **)argv, argc);

  switch (cmd) {
  case CLI_INVALID:
    printf("invalid\n");
    break;
  case CLI_HELP:
    printf("help\n");
    break;
  case CLI_STATS:
    printf("stats\n");
    break;
  case CLI_RUN:
    printf("run\n");
    break;
  }

  int len;
  CubeMove *list = generate_scramble(&len);
  if (list == NULL) {
    return 1;
  }

  for (int i = 0; i < len; i++) {
    printf("%s ", cube_move_str(list[i]));
  }
  printf("\n");

  return 0;
}
