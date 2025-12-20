#include <string.h>

#include "cli.h"

CliCmd parse_args(const char *const *input, int len) {
  if (len <= 1) {
    return CLI_INVALID;
  }

  if (strcmp(input[1], "run") == 0) {
    return CLI_RUN;
  } else if (strcmp(input[1], "stats") == 0) {
    return CLI_STATS;
  } else if (strcmp(input[1], "help") == 0) {
    return CLI_HELP;
  }

  return CLI_INVALID;
}
