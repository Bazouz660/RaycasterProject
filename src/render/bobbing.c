/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** bobbing.c
*/

#include "structs.h"
#include "prototypes.h"

void apply_bobbing(core_t *c, bool enable)
{
    float bobbing_speed = 2;
    static bool do_head_bobbing = false;

    if (!enable)
        return;
    if (vect_mag(c->player->vel) > 0.1 ||
        (sfView_getCenter(c->render3d.view).y > c->render.r_size.y - 0.1
        && sfView_getCenter(c->render3d.view).y < c->render.r_size.y + 0.1)) {
        do_head_bobbing = true;
        c->render3d.bobbing_clock += 1;
    }
    sfView_setCenter(c->render3d.view,
    (sfVector2f){sfView_getCenter(c->render3d.view).x,
    ((sin(c->render3d.bobbing_clock * bobbing_speed * 0.1) *\
    vect_mag(c->player->vel) * (2.0 * ((float)c->render.r_size.x /\
    (float)SCREEN_WIDTH)))) + (c->render.r_size.y / 2)});
}
