/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** base_update.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

void update_clock(core_t *c)
{
    c->clock.time = sfClock_getElapsedTime(c->clock.clock);
    c->clock.seconds = c->clock.time.microseconds/1000000.0;
}

float get_frame_delta(core_t *c)
{
    float prev_time = time_as_sec(c->clock.prev_time);
    float current_time = c->clock.seconds;
    float frame_delta = (current_time - prev_time);

    return frame_delta;
}

void update_fps(core_t *c)
{
    static float clock = 0;
    float fps = 0;

    c->clock.frame_delta = get_frame_delta(c);
    c->clock.elapsed_time = c->clock.frame_delta * 80;
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
