#include "charge.h"

void compute_e(charge c, vec p, vec *e){    
    vec qP = vec_sub(p, c.pos);
    double norm_qP = normalize(qP);
    double e_2 = K * c.q / (norm_qP * norm_qP);
    *e = mult(div_with_scalar(qP, norm_qP), e_2);
}

void compute_total_normalized_e(charge *charges, int num_charges, vec p, vec *e){
    vec previous_e;
    vec *current_e = e;
    for (int i = 0; i < num_charges; i++){
        compute_e(charges[i], p, current_e);
        *current_e = vec_add(*e, previous_e);
        previous_e = *current_e;
    }
    *e = *current_e; 
}

bool is_position_valid(vec v, universe u){
    return (v.x >= u.x0 && v.x < u.x1 && v.y >= u.y0 && v.y < u.y1) ? true : false;
}

void draw_field_line(struct gfx_context_t *ctxt, charge *charges, int num_charges, double dx, vec pos0, universe u, 
int screen_x, int screen_y, uint32_t color){
    vec e = {.x = 0, .y = 0};

    for(int i = 0; i < num_charges; i++){
    vec current_p = pos0;

        while (is_position_valid(current_p, u)){
            bool break_process = false;
            compute_total_normalized_e(charges, num_charges, current_p, &e);
            vec next_p;
            if (i % 2 == 0){
                next_p = vec_add(current_p, mult(div_with_scalar(e, normalize(e)), dx));
                color = COLOR_RED;
            } else {
                next_p = vec_sub(current_p, mult(div_with_scalar(e, normalize(e)), dx));
                color = COLOR_BLUE;
            }
            
            for (int j = 0; j < num_charges; j++){
                vec distance = vec_sub(charges[j].pos, next_p);
                if (normalize(distance) < 0.03) break_process = true;
            }

            gfx_draw_line(ctxt, position_to_coordinates(screen_x, screen_y, u, current_p), position_to_coordinates(screen_x, screen_y, u, next_p), color);
            current_p = next_p;
            if (break_process) break;
        }
    }
}

void draw_plus(struct gfx_context_t *ctxt, coordinates center, int r, uint32_t color){
    int length = r/2;

    coordinates line_end = coordinates_create(center.y + length, center.x);//NORTH
    gfx_draw_line(ctxt, center, line_end, color);
    line_end = coordinates_create(center.y - length, center.x);//SOUTH
    gfx_draw_line(ctxt, center, line_end, color);
    line_end = coordinates_create(center.y , center.x + length);//EAST
    gfx_draw_line(ctxt, center, line_end, color);
    line_end = coordinates_create(center.y, center.x - length);//WEST
    gfx_draw_line(ctxt, center, line_end, color);
}

void draw_minus(struct gfx_context_t *ctxt, coordinates center, int r, uint32_t color){
    int length = r / 2;
    coordinates line_end = coordinates_create(center.y , center.x + length);//EAST
    gfx_draw_line(ctxt, center, line_end, color);
    line_end = coordinates_create(center.y, center.x - length);//WEST
    gfx_draw_line(ctxt, center, line_end, color);
}

void draw_charges(struct gfx_context_t *context, charge *charges, int num_charges, int r, uint32_t color, 
int screen_x, int screen_y, universe u){
    for (int i = 0; i < num_charges; i++){
        coordinates center = position_to_coordinates(screen_x, screen_y, u , charges[i]. pos);
        gfx_draw_circle(context, center,  r, color);

        if (charges[i].q >= 0){
            draw_plus(context, center, r, color);
        }else{
            draw_minus(context, center, r, color);
        }
    }
}

void gfx_draw_line(struct gfx_context_t *ctxt, coordinates p0, coordinates p1, uint32_t color){
    int dy = p1.y - p0.y;
    int dx = p1.x - p0.x;
    int m_dx = p0.x - p1.x;
    int m_dy;
    int a, e, y, x;

    if (dy >= 0){
        if (dy <= dx){
            a = 2*dy;
            e = 0;
            y = p0.y;

            for(x = p0.x; x < p1.x; x++){
                gfx_putpixel(ctxt, x, y, color);
                e+=a;
                if (e>=dx){
                    y+=1;
                    e-= 2*dx;
                }
            }
        } else if (dx >=0 && dx < dy){
            a = 2*dx;
            e = 0;
            x = p0.x;

            for(y = p0.y; y < p1.y; y++){
                gfx_putpixel(ctxt, x, y, color);
                e+=a;
                if (e>=dx){
                    x+=1;
                    e-= 2*dy;
                }
            }
        } else if (dy >= m_dx){
            a = 2*dx;
            e=0;
            m_dy = p0.y - p1.y;
            x = p0.x;

            for(y = p0.y; y < p1.y; y++){
                gfx_putpixel(ctxt, x, y, color);
                e+=a;
                if (e<=m_dy){
                    x-=1;
                    e+= 2*dy;
                }
            }
        }else {gfx_draw_line(ctxt, p1, p0, color);}
    }else{
        if (m_dx <= dy){
            a = 2*dy;
            e = 0;
            y = p0.y;
            for (int x = p0.x; x < p1.x; x++){
                gfx_putpixel(ctxt, x, y, color);
                e+= a;
                if (e <= m_dx){
                    y -= 1;
                    e += 2*dx;
                }
            }
        }else {
            gfx_draw_line(ctxt, p1, p0, color);
        }
    }
}

void gfx_draw_circle(struct gfx_context_t *ctxt, coordinates c, uint32_t r, uint32_t color){
    uint32_t x = 0;
    uint32_t y = r;
    uint32_t d = r - 1;

    while(y >= x){
        gfx_putpixel(ctxt, c.x + x, c.y + y, color);
        gfx_putpixel(ctxt, c.x + y, c.y + x, color);
        gfx_putpixel(ctxt, c.x - x, c.y + y, color);
        gfx_putpixel(ctxt, c.x - y, c.y + x, color);
        gfx_putpixel(ctxt, c.x + x, c.y - y, color);
        gfx_putpixel(ctxt, c.x + y, c.y - x, color);
        gfx_putpixel(ctxt, c.x - x, c.y - y, color);
        gfx_putpixel(ctxt, c.x - y, c.y - x, color);

        if (d >= (2*x)){
            d = d - (2 * x) - 1;
            x = x + 1;
        } else if(d < 2*(r - y)) {
            d = d + (2 * y) - 1;
            y = y - 1;
        } else {
            d = d + 2 * (y-x-1);
            y = y - 1;
            x = x + 1;
        }
    }
}