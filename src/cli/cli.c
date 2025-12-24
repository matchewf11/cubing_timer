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
  } else if (strcmp(input[1], "delete") == 0) {
    return CLI_DELETE;
  } else if (strcmp(input[1], "plus2") == 0) {
    return CLI_PLUS_TWO;
  } else if (strcmp(input[1], "typing") == 0) {
    return CLI_TYPING;
  } else if (strcmp(input[1], "virtual") == 0) {
    return CLI_VIRTUAL;
  } else if (strcmp(input[1], "genscram") == 0) {
    return CLI_GEN_SCRAM;
  }

  return CLI_INVALID;
}
