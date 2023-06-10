#include "vector.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>

coordinates coordinates_create(int row_, int column_)
{
    coordinates c = {.y = row_, .x = column_};
    return c;
}

// Transform a position in the univers [x0,x1] x [y0,y1] to a screen position
coordinates position_to_coordinates(int width, int height, universe u, vec pos)
{
    double dx = u.x1 - u.x0;
    double dy = u.y1 - u.y0;
    return coordinates_create((int)round(height * (pos.y - u.y0) / dy), (int)round(width * (pos.x - u.x0) / dx));
}

double rand_one()
{
    return (double)rand() / (double)RAND_MAX;
}

charge charge_create(double q, vec pos)
{
    charge c = {.q = q, .pos = pos};
    return c;
}