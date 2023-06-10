#include "vector.h"

void vec_init( vec *v, double x, double y){
    v->x = x;
    v->y = y;
}

double normalize(vec vector){
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}


double angle(vec vector) {
    return atan2(vector.y, vector.x);
}

vec vec_add( vec vec1, vec vec2) {
     vec vectorResult;

    vectorResult.x = vec1.x + vec2.x;
    vectorResult.y = vec1.y + vec2.y;
    
    return vectorResult;
}

void vec_add_in_place( vec *vec1, vec vec2) {
    vec1->x = vec1->x + vec2.x;
    vec1->y = vec1->y + vec2.y;
}


void vec_sub_in_place( vec *vec1, vec vec2) {
    vec1->x = vec1->x - vec2.x;
    vec1->y = vec1->y - vec2.y;
}

vec mult( vec vec1, double scalaire) {
     vec vectorResult;

    vectorResult.x = vec1.x * scalaire;
    vectorResult.y = vec1.y * scalaire;
    
    return vectorResult;
}

vec vec_sub(vec vec1, vec vec2){
    vec2.x *= -1;
    vec2.y *= -1;

    return vec_add(vec1, vec2);
}

void mult_in_place( vec *vec, double scalaire) {
    vec->x = vec->x * scalaire;
    vec->y =  vec->y * scalaire;
}

bool compare_vec(vec a, vec b) {
    return a.x == b.x && a.y == b.y;
}

vec div_with_scalar( vec vec1, double scalaire) {
    vec vectorResult;

    vectorResult.x = vec1.x / scalaire;
    vectorResult.y = vec1.y / scalaire;
    
    return vectorResult;
}

void print(vec vector) {
    //%e.10
    printf("x : %f \n", vector.x);
    printf("y : %f \n", vector.y);
    printf("Norme : %f \n", normalize(vector));
    printf("Angle : %f \n", angle(vector));
}