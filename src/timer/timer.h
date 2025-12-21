#ifndef TIMER_H
#define TIMER_H

#include "../scramble/scramble.h"

// return 0 if ok
// return -1 if error
// Be sure to free out_moves
// Only use if return 0
int start_cube_timer(double *out_time, CubeMove **out_moves,
                     int *out_moves_len);

#endif
