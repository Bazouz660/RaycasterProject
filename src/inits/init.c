/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** init.c
*/

#include "buttons.h"

void init_player(core_t *c)
{
    c->entities = NULL;
    add_entity(c, &c->entities, (sfVector2f){1000, 500}, 0);
    c->player = c->entities;
}

void init_fps_text(core_t *c)
{
    c->ui.font = sfFont_createFromFile("misc/font.ttf");
    c->render.fps_hint = sfText_create();
    sfText_setFont(c->render.fps_hint, c->ui.font);
    sfText_setColor(c->render.fps_hint, sfWhite);
    sfText_setPosition(c->render.fps_hint, (sfVector2f){30, 30});
    sfText_setString(c->render.fps_hint, NULL);
}

void load_level(core_t *c, level_models_t model)
{
    sfVector2f bpos = {32, 32};
    sfVector2f pos = bpos;
    int type = 0;

    c->render.render_distance = 2000;
    c->level.c_size = (sfVector2f){64, 64};
    c->level.dim.x = model.x;
    c->level.dim.y = model.y;
    c->level.nb_case = (c->level.dim.x * c->level.dim.y);
    c->level.gridc = malloc(sizeof(grid_case_t **) * \
    (c->level.nb_case + 1));
    for (int i = 0; i < c->level.dim.y; i++) {
        c->level.gridc[i] = malloc(sizeof(grid_case_t *) * (c->level.dim.x + 1));
        for (int j = 0; j < c->level.dim.x; j++) {
            c->level.gridc[i][j] = new_grid_case(i, model.matrix[i][j],
            pos, c->level.c_size,
            j, i);
            pos.x += c->level.c_size.x;
        }
        pos.y += c->level.c_size.y;
        pos.x = bpos.x;
        c->level.gridc[i][c->level.dim.x] = NULL;
    }
    c->level.gridc[c->level.nb_case] = NULL;
}

void init_level(core_t *c)
{
    c->ui.selected_level = 0;
    c->render.nb_levels = load_level_matrices(c);
}

void init_view(core_t *c)
{
    c->render.view = sfView_create();
    c->render3d.view = sfView_create();
    sfView_setSize(c->render.view, (sfVector2f){sfRenderWindow_getSize(c->render.window).x,
    sfRenderWindow_getSize(c->render.window).y});
    sfView_setSize(c->render3d.view, (sfVector2f){sfRenderWindow_getSize(c->render.window).x,
    sfRenderWindow_getSize(c->render.window).y});
    sfView_setViewport(c->render.view, (sfFloatRect){0, 0, 0.3, 0.3});
    sfView_setCenter(c->render.view, sfView_getCenter(sfRenderWindow_getView(c->render.window)));
    sfView_setCenter(c->render3d.view, sfView_getCenter(c->render.view));
    sfRenderWindow_setView(c->render.window, c->render3d.view);
}

void init_render3d(core_t *c)
{
    c->render3d.sky = vrect_create();
    c->render3d.ground = vrect_create();
    c->render3d.vertical_angle = 0;
    sfVector2f pos;
    sfVector2f w_size = {sfRenderWindow_getSize(c->render.window).x,
    sfRenderWindow_getSize(c->render.window).y};

    c->render.nb_rays = c->render.w_size.x;
    c->render3d.fov = 70;
    vrect_setcolor(c->render3d.sky, (sfColor){180, 180, 100, 255}, 0, true);
    vrect_setcolor(c->render3d.sky, darken_color((sfColor){180, 180, 100,
    255}, 0.2), 2, false);
    vrect_setcolor(c->render3d.sky, darken_color((sfColor){180, 180, 100,
    255}, 0.2), 3, false);
    vrect_setsize(c->render3d.sky, (sfVector2f){w_size.x, w_size.y / 2});
    pos = sfView_getCenter(c->render3d.view);
    pos.y -= w_size.y / 2;
    pos.x -= w_size.x / 2;
    vrect_setposition(c->render3d.sky, pos);
    pos.y += w_size.y / 2;
    vrect_setsize(c->render3d.ground, (sfVector2f){w_size.x, w_size.y / 2});
    vrect_setposition(c->render3d.ground, pos);
    vrect_setcolor(c->render3d.ground, (sfColor){129 * 1.4,92 * 1.4,21 * 1.4,255}, 0, true);
    vrect_setcolor(c->render3d.ground, darken_color((sfColor){129,92,21,255},
    0.1), 0, false);
    vrect_setcolor(c->render3d.ground, darken_color((sfColor){129,92,21,255},
    0.1), 1, false);
    c->render3d.walls = NULL;
    c->render3d.depth_buffer = malloc(sizeof(float) * c->render.w_size.x);
}

void init_textures(core_t *c)
{
    c->textures.wall = malloc(sizeof(sfTexture *) * (5));
    c->textures.wall[0] = sfTexture_createFromFile("assets/walls/brick.jpg",
    NULL);
    c->textures.wall[1] = sfTexture_createFromFile("assets/walls/brick2.jpg",
    NULL);
    c->textures.wall[2] = sfTexture_createFromFile("assets/walls/door.jpg",
    NULL);
    c->textures.wall[3] = sfTexture_createFromFile("assets/walls/tile.jpg",
    NULL);
    c->textures.wall[4] = NULL;
    c->textures.button[0] = sfTexture_createFromFile("assets/buttons/play.png",
    NULL);
    c->textures.button[1] = sfTexture_createFromFile("assets/buttons/exit.png",
    NULL);
    c->textures.button[2] = sfTexture_createFromFile("assets/buttons/lvl_select.png",
    NULL);
    c->textures.button[3] = sfTexture_createFromFile("assets/buttons/next.png",
    NULL);
    c->textures.button[4] = sfTexture_createFromFile("assets/buttons/prev.png",
    NULL);
    c->textures.background[0] = sfTexture_createFromFile("assets/backgrounds/main_menu.jpg",
    NULL);
    c->textures.enemy[0] = sfTexture_createFromFile("assets/enemies/amogus.png", NULL);
}

void init_mouse(core_t *c)
{
    c->mouse.pos = get_mouse_pos_view(c);
    c->ui.mouse_released = true;
}

void init_buttons(core_t *c)
{
    c->ui.button = malloc(sizeof(button_t *) * 6);

    c->ui.button[0] = button_create(c->textures.button[0],
    (sfVector2f){400, 120}, (sfVector2f){960, 440});
    button_set_update(c->ui.button[0]);
    button_set_onclick(c->ui.button[0], &on_click_play);
    button_link_scene(c->ui.button[0], 0);

    c->ui.button[1] = button_create(c->textures.button[1],
    (sfVector2f){400, 120}, (sfVector2f){960, 600});
    button_set_update(c->ui.button[1]);
    button_set_onclick(c->ui.button[1], &on_click_exit);
    button_link_scene(c->ui.button[1], 0);

    c->ui.button[2] = button_create(c->textures.button[2],
    (sfVector2f){400, 120}, (sfVector2f){960, 600});
    button_set_update(c->ui.button[2]);
    button_set_onclick(c->ui.button[2], &on_click_selec_lvl);
    button_link_scene(c->ui.button[2], 1);

    c->ui.button[3] = button_create(c->textures.button[3],
    (sfVector2f){100, 120}, (sfVector2f){1235, 600});
    button_set_update(c->ui.button[3]);
    button_set_onclick(c->ui.button[3], &on_click_next);
    button_link_scene(c->ui.button[3], 1);

    c->ui.button[4] = button_create(c->textures.button[4],
    (sfVector2f){100, 120}, (sfVector2f){680, 600});
    button_set_update(c->ui.button[4]);
    button_set_onclick(c->ui.button[4], &on_click_prev);
    button_link_scene(c->ui.button[4], 1);

    c->ui.button[5] = NULL;
}

void init_background(core_t *c)
{
    c->ui.b1 = sfRectangleShape_create();

    sfRectangleShape_setSize(c->ui.b1, (sfVector2f){c->render.w_size.x,
    c->render.w_size.y});
    sfRectangleShape_setOrigin(c->ui.b1, get_rect_center(c->ui.b1));
    sfRectangleShape_setFillColor(c->ui.b1, sfBlack);
    //sfRectangleShape_setTexture(c->ui.b1, c->textures.background[0], false);
    sfRectangleShape_setPosition(c->ui.b1, sfView_getCenter(c->render3d.view));
}

void init_ui(core_t *c)
{
    init_background(c);
    init_buttons(c);
    c->ui.level_selec_text = sfText_create();
    sfText_setFillColor(c->ui.level_selec_text, sfWhite);
    sfText_setFont(c->ui.level_selec_text, c->ui.font);
    sfText_setPosition(c->ui.level_selec_text, (sfVector2f){c->render.w_size.x / 2,
    c->render.w_size.y * 0.8});
    sfText_setString(c->ui.level_selec_text, my_strcat("1 / ", my_int_to_str(c->render.nb_levels)));
    sfText_setOrigin(c->ui.level_selec_text,
    get_text_center(c->ui.level_selec_text));
}

void init_entities(core_t *c)
{
    add_entity(c, &c->entities, (sfVector2f){300, 300}, 1);
}

void init_game(core_t *c)
{
    c->render.window = create_window("Backrooms");
    c->render.w_size = sfRenderWindow_getSize(c->render.window);
    sfRenderWindow_setPosition(c->render.window, (sfVector2i){0, 0});
    c->clock.clock = sfClock_create();
    c->mouse.lastpos = get_mouse_pos_view(c);
    c->mouse.diff = (sfVector2i){0, 0};
    c->render.scene = 0;
    c->clock.prev_time.microseconds = 0;
    srand(time(NULL));
    init_textures(c);
    init_view(c);
    init_mouse(c);
    init_fps_text(c);
    init_level(c);
    init_player(c);
    init_entities(c);
    init_render3d(c);
    init_ui(c);
}
