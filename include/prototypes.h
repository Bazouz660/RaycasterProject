/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** prototypes.h
*/

#include "includes.h"
#include "structs.h"
#include "defines.h"

#ifndef RAYCASTER_PROTOTYPES
    #define RAYCASTER_PROTOTYPES

    // Utils
    sfRenderWindow *create_window(sfVector2u size, char const *title);
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
    sfColor darken_color(sfColor c1, double prog);
    char *my_strcpy(char *dest, char const *src);
    char *my_strcat(char *dest, char const *src);
    int my_strcmp(char const *s1, char const *s2);
    char **strwar(const char *str, const char *separators);
    char *rm_str_char(char **str, char *to_remove);
    char *str_keep_char(char **str, char *to_keep);
    int my_getnbr(char const *str);
    sfVector2i get_mouse_pos_view(core_t *c);
    sfBool get_mouse_intersect_view(core_t *c, sfFloatRect to_check);
    sfVector2f get_text_center(sfText *text);
    double clamp(double min, double max, double n);
    int get_inv_angle(double angle);
    void close_game(core_t *c);
    double norm_deg(double *value, const double start, const double end);
    int my_list_size(entity_t const *begin);
    float lerp(float a, float b, float t);
    sfVector2f lerp2f(sfVector2f a, sfVector2f b, float t);

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
    sfVector2f v2u_to_v2f(sfVector2u vector);
    sfVector2u v2f_to_v2u(sfVector2f vector);
    sfVector2i v2f_to_v2i(sfVector2f vector);
    sfVector2f v2i_to_v2f(sfVector2i vector);

    // Level
    grid_case_t *new_grid_case(int index, int type, sfVector2f pos,
    sfVector2f size, int ix, int iy);
    int load_level_matrices(core_t *c);
    void load_level(core_t *c, level_models_t model);

    // Matrix
    matrix_t new_matrix(int rows, int cols);
    matrix_t new_rot_matrix(float angle);
    sfVector2f multiply_vec(matrix_t *mx, sfVector2f vec);
    void free_matrix(matrix_t *matrix);

    // Entities
    void add_entity(core_t *c, entity_t **head, sfVector2f pos, int id);
    void entity_reposition(core_t *c, entity_t *entity);
    void update_entities(core_t *c);
    entity_t *new_entity(core_t *c, sfVector2f pos, int id);

    // Render
    void draw_all(core_t *c);

    // Collision
    void check_level_collisions(core_t *, level_t level, entity_t* entity);

    // Raycasting
    void cast_rays(core_t *c, entity_t *src);
    void cast_floor(core_t *c, sfTexture *texture);

    // 3d map
    void add_wall(core_t *c, wall3d_t **head, ray_t ray, int fov);
    void del_wall(wall3d_t **head, wall3d_t *del_node);
    void del_walls(core_t *c);

    // vrect
    vrect_t *vrect_create(void);
    void vrect_draw(sfRenderWindow *render_window, sfRenderTexture *render_texture, vrect_t *vrect);
    void vrect_settexture(vrect_t *vrect, sfTexture *texture);
    void vrect_setposition(vrect_t *vrect, sfVector2f position);
    void vrect_setsize(vrect_t *vrect, sfVector2f size);
    void vrect_setcolor(vrect_t *vrect, sfColor color, unsigned int side,
    bool all_sides);

    // Buttons
    button_t *button_create(sfTexture *texture, sfVector2f size, sfVector2f pos);
    void button_set_onclick(button_t *button, void(*func)(core_t *, button_t *));
    void button_set_update(button_t *button);
    void button_link_scene(button_t *button, unsigned short scene);
    void button_destroy(button_t *button);

    // UI
    void draw_main_menu(core_t *c);
    void draw_select_menu(core_t *c);

    // Pathfinding
    void find_dist_to_player(core_t *c, entity_t *entity);
    float find_target(core_t *c, entity_t *entity, sfVector2f target);

    // Rendering
    void draw_entity3d(core_t *c, entity_t *entity);
    void apply_bobbing(core_t *c, bool enable);

    // Memory cleanup
    void free_all(core_t *c);
    void free_entities(entity_t *list);
    void free_level(core_t *c);
    void free_render(core_t *c);
    void free_textures(core_t *c);
    void free_ui(core_t *c);

#endif /*RAYCASTER_PROTOTYPES*/
