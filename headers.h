#include <graphics.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

#define vertex 8
#define rib_count 12
#define side_count 6
#define width 640
#define height 480
#define UP_KEY 72
#define LEFT_KEY 75
#define DOWN_KEY 80
#define RIGHT_KEY 77
#define MINUS_KEY 45
#define PLUS_KEY 61
#define W_KEY 119
#define S_KEY 115
#define A_KEY 97
#define D_KEY 100
#define Z_KEY 122
#define X_KEY 120
#define ESC_KEY 27

#define PI acos(-1.0)
#define X(x) ((1.0 / 2) * (x + 1) * width)
#define Y(y) ((-1.0 / 2) * (y - 1) * height)