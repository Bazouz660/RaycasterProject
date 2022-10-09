/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** base_update.c
*/

#include "my.h"

void update_clock(core_t *c)
{
    c->clock.time = sfClock_getElapsedTime(c->clock.clock);
    c->clock.seconds = c->clock.time.microseconds/1000000.0;
}

void update_fps(core_t *c)
{
    static float clock = 0;
    float fps = 0;

    fps = get_fps(c->clock.clock, &c->clock.prev_time);
    if (c->clock.seconds > clock + 0.2) {
        clock = c->clock.seconds;
        sfText_setString(c->render.fps_hint, my_int_to_str((int)fps));
    }
}

void update_screen(core_t *c)
{
    sfRenderWindow_display(c->render.window);
    sfRenderWindow_clear(c->render.window, sfBlack);
}
