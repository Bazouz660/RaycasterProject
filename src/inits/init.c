/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** init.c
*/

#include "my.h"

void init_player(core_t *c)
{
    c->entities = NULL;
    add_entity(&c->entities, (sfVector2f){1000, 500}, 0);
}

void init_fps_text(core_t *c)
{
    c->render.fps_hint = sfText_create();
    sfText_setFont(c->render.fps_hint, sfFont_createFromFile("misc/font.ttf"));
    sfText_setColor(c->render.fps_hint, sfWhite);
    sfText_setPosition(c->render.fps_hint, (sfVector2f){30, 30});
    sfText_setString(c->render.fps_hint, NULL);
}

void init_level(core_t *c)
{
    sfVector2f bpos = {32, 32};
    sfVector2f pos = bpos;
    int type = 0;

    c->render.render_distance = 2000;
    c->level.c_size = (sfVector2f){64, 64};
    c->level.dim.x = 30;
    c->level.dim.y = 17;
    c->level.nb_case = (c->level.dim.x * c->level.dim.y);
    c->level.gridc = malloc(sizeof(grid_case_t **) * \
    (c->level.nb_case + 1));
    for (int i = 0; i < c->level.dim.y; i++) {
        c->level.gridc[i] = malloc(sizeof(grid_case_t *) * (c->level.dim.x + 1));
        for (int j = 0; j < c->level.dim.x; j++) {
            if (random_number(-1, 10) > 0) {
                type = 0;
            } else
                type = random_number(1, 5);
            if (i == 0 || j == 0 || i + 1 == c->level.dim.y || j + 1 == c->level.dim.x) {
                type = 1;
            }
            c->level.gridc[i][j] = new_grid_case(i, type, pos, c->level.c_size, j, i);
            pos.x += c->level.c_size.x;
        }
        pos.y += c->level.c_size.y;
        pos.x = bpos.x;
        c->level.gridc[i][c->level.dim.x] = NULL;
    }
    c->level.gridc[c->level.nb_case] = NULL;
}

void init_view(core_t *c)
{
    sfRenderWindow_setMouseCursorVisible(c->render.window, sfFalse);
    c->render.view = sfView_create();
    c->render3d.view = sfView_create();
    sfView_setSize(c->render.view, (sfVector2f){sfRenderWindow_getSize(c->render.window).x, sfRenderWindow_getSize(c->render.window).y});
    sfView_setSize(c->render3d.view, (sfVector2f){sfRenderWindow_getSize(c->render.window).x, sfRenderWindow_getSize(c->render.window).y});
    sfView_setViewport(c->render.view, (sfFloatRect){0, 0, 0.3, 0.3});
    sfView_setCenter(c->render.view, sfView_getCenter(sfRenderWindow_getView(c->render.window)));
    sfView_setCenter(c->render3d.view, sfView_getCenter(c->render.view));
    sfRenderWindow_setView(c->render.window, c->render.view);
}

void init_render3d(core_t *c)
{
    c->render3d.sky = sfRectangleShape_create();
    c->render3d.ground = sfRectangleShape_create();
    sfVector2f pos;

    sfRectangleShape_setFillColor(c->render3d.sky, (sfColor){0, 80, 180, 255});
    sfRectangleShape_setSize(c->render3d.sky, (sfVector2f){sfRenderWindow_getSize(c->render.window).x,
    sfRenderWindow_getSize(c->render.window).y});
    sfRectangleShape_setOrigin(c->render3d.sky, get_rect_center(c->render3d.sky));
    pos = sfView_getCenter(c->render3d.view);
    pos.y -= sfRenderWindow_getSize(c->render.window).y / 2;
    sfRectangleShape_setPosition(c->render3d.sky, pos);
    c->render3d.ground = sfRectangleShape_copy(c->render3d.sky);
    sfRectangleShape_setFillColor(c->render3d.ground, (sfColor){20, 10, 10, 255});
    pos.y += sfRenderWindow_getSize(c->render.window).y;
    sfRectangleShape_setPosition(c->render3d.ground, pos);
    c->render3d.walls = NULL;
}

void init_textures(core_t *c)
{
    c->textures.wall[0] = sfTexture_createFromFile("assets/walls/brick.jpg", NULL);
    c->textures.wall[1] = NULL;
}

void init_mouse(core_t *c)
{
    c->mouse.pos.x = sfMouse_getPositionRenderWindow(c->render.window).x;
    c->mouse.pos.y = sfMouse_getPositionRenderWindow(c->render.window).y;
}

void init_game(core_t *c)
{
    c->render.window = create_window("Raycaster");
    sfRenderWindow_setPosition(c->render.window, (sfVector2i){0, 0});
    c->clock.clock = sfClock_create();
    c->mouse.lastpos.x = sfMouse_getPositionRenderWindow(c->render.window).x;
    c->mouse.lastpos.y = sfMouse_getPositionRenderWindow(c->render.window).y;
    c->mouse.diff = (sfVector2i){0, 0};
    srand(time(NULL));
    init_textures(c);
    init_view(c);
    init_mouse(c);
    init_fps_text(c);
    init_level(c);
    init_player(c);
    init_render3d(c);
}
