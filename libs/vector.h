#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef struct _vec{
    double x,y;
} vec;

void vec_init(vec *v, double x, double y);
double normalize(vec vector);
vec vec_add(vec vec1, vec vec2);
vec mult(vec vec1, double scalaire);
void vec_add_in_place(vec *vec1, vec vec2);
void vec_sub_in_place(vec *vec1, vec vec2);
vec vec_sub(vec vec1, vec vec2);
void mult_in_place(vec *vec, double scalaire);
double angle(vec vector);
bool compare_vec(vec a, vec b);
vec div_with_scalar(vec vec1, double scalaire);
void print(vec vector);

#endif