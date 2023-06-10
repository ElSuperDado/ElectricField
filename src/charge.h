#ifndef _CHARGE_H_
#define _CHARGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h> 
#include <stdint.h> 
#include <math.h>
#include "../libs/gfx.h"
#include "../libs/vector.h"
#include "../libs/utils.h"
#define K 8.988e9
#define E 1.602e-19


// Compute E*qP/norm(qP)
void compute_e(charge c, vec p, vec *e);

// Compute the normalized sum of Ei*qiP/norm(qiP)
void compute_total_normalized_e(charge *charges, int num_charges, vec p, vec *e);

// Compute and then draw all the points belonging to a field line,
// starting from pos0.
void draw_field_line(struct gfx_context_t *ctxt, charge *charges, int num_charges, double dx, vec pos0,
universe u, int screen_x, int screen_y, uint32_t color);

bool is_position_valid(vec v, universe u);

// Draw all the charges
// A circle with minus sign for negative charges
// A circle with a plus sign for positive charges
void draw_charges(struct gfx_context_t *context, charge *charges, int num_charges, int r, uint32_t color, 
int screen_x, int screen_y, universe u);


void gfx_draw_line(struct gfx_context_t *ctxt, coordinates p0,
coordinates p1, uint32_t color);

void gfx_draw_circle(struct gfx_context_t *ctxt, coordinates c,
uint32_t r, uint32_t color);



#endif