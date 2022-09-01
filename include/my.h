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
#define DR 0.0174533

#define bool int

#define TransparentRed (sfColor){255, 0, 0, 100}

typedef struct intersection_s {
    float cx;
    float cy;
    float time;
    float nx;
    float ny;
    float ix;
    float iy;
} intersection_t;

typedef struct matrix_s {
    int rows;
    int cols;
    float **data;
} matrix_t;

typedef struct grid_case_s {
    int index;
    int type;
    sfRectangleShape *shape;
    sfVector2f pos;
} grid_case_t;

typedef struct level_s {
    sfVector2i dim;
    sfVector2f c_size;
    int nb_case;
    grid_case_t ***gridc;
} level_t;

typedef struct ofrect_s {
    sfVector2f a;
    sfVector2f b;
    sfVector2f c;
    sfVector2f d;
} ofrect;

typedef struct ray_s {
    sfVertex v1;
    sfVertex v2;
    float angle;
    float wall_dist;
    int type;
    int side;
    int index;
} ray_t;

typedef struct render_s {
    sfRenderWindow *window;
    sfView *view;
    sfText *fps_hint;
    ray_t *rays;
    int nb_rays;
    float render_distance;
    sfVector2i ray_pos;
} render_t;

typedef struct wall3d_s {
    int index;
    sfRectangleShape *section;
    struct wall3d_s *next;
    struct wall3d_s *prev;
} wall3d_t;

typedef struct render3d_s {
    sfView *view;
    sfRectangleShape *sky;
    sfRectangleShape *ground;
    wall3d_t *walls;
} render3d_t;

typedef struct clock_s {
    sfClock *clock;
    sfTime time;
    sfTime prev_time;
    float seconds;
} clock_st;

typedef struct sounds_s {
} sounds_t;

typedef struct textures_s {
    sfTexture *wall[2];
} textures_t;

typedef struct mouse_s {
    sfVector2i pos;
    sfVector2i lastpos;
    sfVector2i diff;
} mouse_t;

typedef struct entity_s {
    int index;
    sfVector2f pos;
    sfVector2f vel;
    sfVector2f acc;
    sfVector2f base_scale;
    sfVector2f scale;
    sfVector2f dir;
    sfVector2f ref_dir;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
    float angle;
    float angle_vel;
    float acceleration;
    bool player;
    struct entity_s *next;
    struct entity_s *prev;
} entity_t;

typedef struct core_s {
    render_t render;
    render3d_t render3d;
    clock_st clock;
    sfEvent e;
    textures_t textures;
    mouse_t mouse;
    sounds_t sounds;
    entity_t *entities;
    level_t level;
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
double absolute(double x);
int get_arr_len(void const **arr);
int my_strlen(char const *str);
char *my_strdup(char const *src);
sfColor smooth_color(sfColor c1, sfColor c2, double prog);

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

// Map
grid_case_t *new_grid_case(int index, int type, sfVector2f pos,
sfVector2f size, int ix, int iy);

// Matrix
matrix_t new_matrix(int rows, int cols);
matrix_t new_rot_matrix(float angle);
sfVector2f multiply_vec(matrix_t *mx, sfVector2f vec);
void free_matrix(matrix_t *matrix);

// Entities
void add_entity(entity_t **head, sfVector2f pos, int id);
void entity_reposition(core_t *c, entity_t *entity);
void update_entities(core_t *c);

// Render
void draw_all(core_t *c);

// Collision
void check_level_collisions(core_t *, level_t level, entity_t* entity);

// Raycasting
void cast_rays(core_t *c, entity_t *src);

// 3d map
void add_wall(core_t *c, wall3d_t **head, ray_t ray, int fov);
void del_wall(wall3d_t **head, wall3d_t *del_node);
void del_walls(core_t *c);
