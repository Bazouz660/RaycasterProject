/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** my.h
*/

#include "SFML/Graphics.h"
#include <SFML/Config.h>
#include <SFML/Audio.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define True 1
#define False 0

#define true True
#define false False

#define PI 3.14159265359

#define bool int

#define TransparentRed (sfColor){255, 0, 0, 100}

typedef struct matrix_s {
    int rows;
    int cols;
    float **data;
} matrix_t;

typedef struct ofrect_s {
    sfVector2f a;
    sfVector2f b;
    sfVector2f c;
    sfVector2f d;
} ofrect;

typedef struct window_s {
    sfRenderWindow *window;
    sfView *view;
    sfText *fps_hint;
} render_t;

typedef struct clock_s {
    sfClock *clock;
    sfTime time;
    sfTime prev_time;
    float seconds;
} clock_st;

typedef struct sounds_s {
} sounds_t;

typedef struct textures_s {
} textures_t;

typedef struct mouse_s {
    sfVector2f pos;
    sfVector2f last_pos;
    sfVector2f diff;
} mouse_t;

typedef struct core_s {
    render_t render;
    clock_st clock;
    sfEvent e;
    textures_t textures;
    mouse_t mouse;
    sounds_t sounds;
} core_t;

// Utils
sfRenderWindow *create_window(char const *title);
sfSprite *new_sprite(char *texture_name, float x, float y);
sfSound *new_sound(sfSound *new_sound, const char *buffer_location);
void init_animated_sprite(sfSprite *sprite, int columns, int rows);
sfSprite *setSprite_pos(sfSprite *sprite, float posX, float posY);
sfVector2f get_sprite_center(sfSprite *sprite);
float random_float(float scale);
int random_number(int min_num, int max_num);
sfVertex add_vertex_circular(float radius,
float i, sfVector2f center);
int positive(int nb);
sfVector2f get_rect_center(sfRectangleShape *rect);
sfFloatRect init_frect(float left, float top, float width, float height);
int rand_range(int lower, int upper);
sfVector2f init_vector2f(float x, float y);
sfIntRect init_irect(int left, int top, int width, int height);
char *my_int_to_str(int nb);
double get_angle(sfVector2f origin, sfVector2f direction);
double rad_to_deg(double angle);
double deg_to_rad(double angle);
void modulate_sound(sfSound *sound);
int get_inv_angle(double angle);
sfColor random_color(void);
float get_min(float a, float b);
float get_max(float a, float b);
ofrect rect_get_oriented_bounds(sfRectangleShape *obj);
void rotate_point(sfVector2f center, float angle, sfVector2f *p);
float absolute(float x);
int get_arr_len(void const **arr);

// Inits
void init_game(core_t *c);

// Fps
float get_fps(sfClock *clock, sfTime *prev_time);
float time_as_sec(sfTime time);

// Screen Update
void update_clock(core_t *c);
void update_fps(core_t *c);
void update_screen(core_t *c);

// Vectors
sfVector2f vect_add(sfVector2f v1, sfVector2f v2);
sfVector2f vect_sub(sfVector2f v1, sfVector2f v2);
float vect_mag(sfVector2f v);
sfVector2f vect_mult(sfVector2f v, float n);
sfVector2f vect_unit(sfVector2f v);
sfVector2f vect_norm(sfVector2f v);
float vect_dot(sfVector2f v1, sfVector2f v2);
float vect_cross(sfVector2f v1, sfVector2f v2);
float dist_from(sfVector2f p1, sfVector2f p2);
sfVector2f closest_point_seg(sfVector2f a, sfVector2f b, sfVector2f p);

// Matrix
matrix_t new_matrix(int rows, int cols);
matrix_t new_rot_matrix(float angle);
sfVector2f multiply_vec(matrix_t *mx, sfVector2f vec);
