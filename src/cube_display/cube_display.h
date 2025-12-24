#ifndef CUBE_DISPLAY_H
#define CUBE_DISPLAY_H

#include "../scramble/scramble.h"

typedef enum { WHITE, YELLOW, BLUE, GREEN, RED, ORANGE } CubeColor;
typedef CubeColor Cube[6][9];

static const Cube DEFAULT_CUBE = {
    {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE},
    {ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE, ORANGE},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN},
    {RED, RED, RED, RED, RED, RED, RED, RED, RED},
    {BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW},
};

void display_scrambled_cube(Cube cube);

void scramble_cube(Cube cube, const CubeMove *moves, int len);

#endif
