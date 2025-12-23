#ifndef CLI_H
#define CLI_H

typedef enum {
  CLI_RUN,
  CLI_STATS,
  CLI_HELP,
  CLI_INVALID,
  CLI_DELETE,
} CliCmd;

CliCmd parse_args(const char *const *input, int len);

#endif
