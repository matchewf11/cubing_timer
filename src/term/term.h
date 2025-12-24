#ifndef TERM_H
#define TERM_H

// only call if enable works
// -1 if error
// 0 if ok
int disable_raw_mode();

// call disble after
// -1 if error
// 0 if ok
// call disable before using other raw mode
int enable_raw_mode();

// call disble after
// -1 if error
// 0 if ok
// call disable before using other raw mode
int enable_raw_virtual();

void clear_term();

#endif
