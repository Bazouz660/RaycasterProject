/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** core.c
*/

#include "my.h"

void analyse_events(core_t *c)
{
    while (sfRenderWindow_pollEvent(c->render.window, &c->e)) {
        if (c->e.type == sfEvtClosed)
            sfRenderWindow_close(c->render.window);
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(c->render.window);
    }
}

void update_mouse(core_t *c)
{
    c->mouse.lastpos = c->mouse.pos;
    c->mouse.pos.x = sfMouse_getPositionRenderWindow(c->render.window).x;
    c->mouse.pos.y = sfMouse_getPositionRenderWindow(c->render.window).y;
    c->mouse.diff.x = c->mouse.pos.x - c->mouse.lastpos.x;
    c->mouse.diff.y = c->mouse.pos.y - c->mouse.lastpos.y;
    if (c->mouse.pos.x >= sfRenderWindow_getSize(c->render.window).x - 1) {
        c->mouse.pos.x = 1;
        c->mouse.lastpos.x = 1;
        sfMouse_setPositionRenderWindow(c->mouse.pos, c->render.window);
    }
    if (c->mouse.pos.x - 1 < 0) {
        c->mouse.pos.x = sfRenderWindow_getSize(c->render.window).x;
        c->mouse.lastpos.x = c->mouse.pos.x;
        sfMouse_setPositionRenderWindow(c->mouse.pos, c->render.window);
    }
}

void update_walls(core_t *c)
{
    for (int i = 0; i < c->render.nb_rays; i++)
        add_wall(&c->render3d.walls, c->render.rays[i], c->render.nb_rays);
}

void render_game(core_t *c)
{
    update_screen(c);
    update_mouse(c);
    update_fps(c);
    update_entities(c);
    update_walls(c);
    draw_all(c);
    analyse_events(c);
}

int game_loop(void)
{
    core_t *c = malloc(sizeof(core_t));
    float clock = 0;

    init_game(c);
    sfRenderWindow_setVerticalSyncEnabled(c->render.window, True);
    while (sfRenderWindow_isOpen(c->render.window)) {
        update_clock(c);
        if (c->clock.seconds > clock + 0.016) {
            clock = c->clock.seconds;
            render_game(c);
        }
    }
}

int main(int ac, char **av)
{
    return game_loop();
}
