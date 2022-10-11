/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** structs.h
*/

#include "defines.h"
#include "includes.h"

#ifndef RAYCASTER_STRUCTS
    #define RAYCASTER_STRUCTS

    typedef struct core_s core_t;
    typedef struct button_s button_t;

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

    typedef struct level_models_s {
        int index;
        int x;
        int y;
        int **matrix;
    } level_models_t;

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
        sfVector2u wall_index;
        sfVector2f dir;
        double wall_x;
        float pos_x;
        float next_pos_x;
        float angle;
        float wall_dist;
        int tex_x;
        int type;
        int side;
        int index;
    } ray_t;

    typedef struct cast_s {
        float left;
        float top;
        float maxlen;
        sfVector2f r_pos;
        sfVector2f dir;
        sfColor color;
        sfVector2i map;
        sfVector2f sideDist;
        sfVector2f deltaDist;
        double perpWallDist;
        sfVector2i step;
        int hit;
        int side;
        float ray_direction;
        float ray_projection_position;
        short current_column;
    } cast_t;

    typedef struct button_s {
        int index;
        bool visible;
        unsigned short scene;
        unsigned short state;
        sfRectangleShape *shape;
        sfTexture *texture;
        sfText *text;
        void (*on_click)(core_t *, button_t *);
        void (*update)(core_t *, button_t *);
    } button_t;

    typedef struct render_s {
        sfRenderWindow *window;
        sfVector2u r_size;
        sfVector2u w_size;
        sfView *view;
        sfText *fps_hint;
        ray_t *rays;
        int nb_rays;
        int nb_levels;
        float render_distance;
        sfVector2i ray_pos;
        unsigned short scene;
    } render_t;

    typedef struct wall3d_s {
        int index;
        sfRectangleShape *section;
        struct wall3d_s *next;
        struct wall3d_s *prev;
    } wall3d_t;

    typedef struct vrect_s {
        sfTexture *texture;
        sfVector2f origin;
        sfVector2f pos;
        sfVector2f size;
        sfColor color;
        sfVertex vertex[4];
    } vrect_t;

    typedef struct render3d_s {
        sfView *view;
        sfRenderTexture *rs_render;
        sfRectangleShape *fs_renderer;
        vrect_t *ground;
        vrect_t *sky;
        wall3d_t *walls;
        sfVertex **fc_buffer;
        sfVertex **fc_buffer_drawable;
        sfVertexBuffer *buffer;
        float bobbing_clock;
        float *depth_buffer;
        int fov;
        float vertical_angle;
        float floor_level;
    } render3d_t;

    typedef struct clock_s {
        sfClock *clock;
        sfTime time;
        sfTime prev_time;
        float frame_delta;
        float elapsed_time;
        float seconds;
    } clock_st;

    typedef struct sounds_s {
    } sounds_t;

    typedef struct textures_s {
        sfTexture **wall;
        sfTexture *button[10];
        sfTexture *background[1];
        sfTexture *enemy[1];
    } textures_t;

    typedef struct find_files_s {
        DIR *d;
        int file;
        struct dirent *dir;
        char *content;
        int file_nb;
        char **found_files;
        int index;
    } find_files_t;

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
        sfVector2f screen_pos;
        sfSprite *w_sprite;
        sfSprite *m_sprite;
        sfRectangleShape *hitbox;
        float angle;
        float angle_vel;
        float acceleration;
        float sprint_speed;
        float pdistance;
        bool player;
        struct entity_s *next;
        struct entity_s *prev;
    } entity_t;

    typedef struct ui_s {
        sfView *view;
        sfFont *font;
        button_t **button;
        sfText *level_selec_text;
        bool mouse_released;
        unsigned short selected_level;
        sfRectangleShape *b1;
    } ui_t;

    struct core_s {
        render_t render;
        render3d_t render3d;
        clock_st clock;
        sfEvent event;
        textures_t textures;
        mouse_t mouse;
        sounds_t sounds;
        entity_t *entities;
        entity_t *player;
        level_t level;
        level_models_t *level_models;
        ui_t ui;
    };
#endif /*RAYCASTER_STRUCTS*/
