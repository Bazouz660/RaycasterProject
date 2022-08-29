/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** init.c
*/

#include "my.h"

void init_fps_text(core_t *c)
{
    c->render.fps_hint = sfText_create();
    sfText_setFont(c->render.fps_hint, sfFont_createFromFile("misc/font.ttf"));
    sfText_setColor(c->render.fps_hint, sfWhite);
    sfText_setPosition(c->render.fps_hint, (sfVector2f){30, 30});
    sfText_setString(c->render.fps_hint, NULL);
}

void init_game(core_t *c)
{
    c->render.window = create_window("Raycaster");
    sfRenderWindow_setPosition(c->render.window, (sfVector2i){0, 0});
    c->clock.clock = sfClock_create();
    c->mouse.last_pos.x = sfMouse_getPositionRenderWindow(c->render.window).x;
    c->mouse.last_pos.y = sfMouse_getPositionRenderWindow(c->render.window).y;
    c->mouse.diff = (sfVector2f){0, 0};
    init_fps_text(c);
}
