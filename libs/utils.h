#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdint.h>


typedef struct _universe{
    int x0, x1, y0, y1;
}universe;

typedef struct{
    int x, y;
} coordinates;

typedef struct{
    double q;
    vec pos;
} charge;

coordinates coordinates_create(int row_, int column_);

// Transform a position in the univers [x0,y0] x [x1,y1] to a screen position
coordinates position_to_coordinates(int width, int height, universe u, vec pos);

double rand_one();

charge charge_create(double q, vec pos);

#endif