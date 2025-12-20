// Source For this Code
// <https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

int disable_raw_mode() {
  return tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1 ? -1 : 0;
}

int enable_raw_mode() {

  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    return -1;
  }

  struct termios raw = orig_termios;

  // ECHO: turn of char echoing
  // ICANON: byte by btye instead of line by line
  raw.c_lflag &= ~(ECHO | ICANON);

  // min bytes
  raw.c_cc[VMIN] = 0;

  // min time to wait
  raw.c_cc[VTIME] = 0;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    return -1;
  }

  return 0;
}

void clear_term() { printf("\033[2J\033[H"); }
