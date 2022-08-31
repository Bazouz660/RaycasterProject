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

void del_walls(core_t *c)
{
    wall3d_t *tmp = c->render3d.walls;

    while (tmp != NULL) {
        del_wall(&c->render3d.walls, tmp);
        tmp = tmp->next;
    }
}

void render_game(core_t *c)
{
    update_screen(c);
    update_fps(c);
    update_entities(c);
    for (int i = 0; i < c->render.nb_rays; i++) {
        add_wall(&c->render3d.walls, c->render.rays[i], c->render.nb_rays);
    }
    draw_all(c);
    del_walls(c);
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
            c->mouse.pos.x = sfMouse_getPositionRenderWindow(c->render.window).x;
            c->mouse.pos.y = sfMouse_getPositionRenderWindow(c->render.window).y;
            render_game(c);
        }
    }
}

int main(int ac, char **av)
{
    return game_loop();
}
