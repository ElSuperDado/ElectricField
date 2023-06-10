#include "src/charge.h"
#define SCREENSIZE_X 700
#define SCREENSIZE_Y 700
#define CHARGE_SIZE 20
#define NB_FIELDS 1000
#define NB_CHARGES 8

int main(){
    universe u = {.x0 = 0, .x1 = 1, .y0 = 0, .y1 = 1};
    vec v_c1 = {.x = 0.3, .y = 0.25};
    vec v_c2 = {.x = 0.3, .y = 0.5};
    vec v_c3 = {.x = 0.3, .y = 0.75};
    vec v_c4 = {.x = 0.7, .y = 0.25};
    vec v_c5 = {.x = 0.7, .y = 0.5};
    vec v_c6 = {.x = 0.7, .y = 0.75};
    vec v_c7 = {.x = 0.5, .y = 0.35};
    vec v_c8 = {.x = 0.5, .y = 0.65};
    charge c1 = charge_create(rand_one() / E * (-1), v_c1);
    charge c2 = charge_create(rand_one() / E, v_c2);
    charge c3 = charge_create(rand_one() / E * (-1), v_c3);
    charge c4 = charge_create(rand_one() / E, v_c4);
    charge c5 = charge_create(rand_one() / E * (-1), v_c5);
    charge c6 = charge_create(rand_one() / E, v_c6);
    charge c7 = charge_create(rand_one() / E, v_c7);
    charge c8 = charge_create(rand_one() / E * (-1), v_c8);

    charge c_list[] = {c1, c2, c3, c4, c5, c6, c7, c8};
    vec p0;
    
    struct gfx_context_t *ctxt = gfx_create("EF", SCREENSIZE_X, SCREENSIZE_Y);
    double delta_x = 1 / sqrt(pow(SCREENSIZE_X, 2) + pow(SCREENSIZE_Y, 2));
    
    for (int i = 0; i < NB_FIELDS; i++){
        vec_init(&p0, rand_one(), rand_one());
        draw_field_line(ctxt, c_list, NB_CHARGES, delta_x, p0, u, SCREENSIZE_X, SCREENSIZE_Y, COLOR_RED);
    }
    draw_charges(ctxt, c_list, NB_CHARGES, CHARGE_SIZE, COLOR_WHITE, SCREENSIZE_X, SCREENSIZE_Y, u);

    while (gfx_keypressed() != SDLK_ESCAPE) gfx_present(ctxt);
    gfx_destroy(ctxt);

    return EXIT_SUCCESS;
}