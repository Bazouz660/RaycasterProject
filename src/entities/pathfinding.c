/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** pathfinding.c
*/

#include "structs.h"
#include "prototypes.h"

void find_dist_to_player(core_t *c, entity_t *entity)
{
    entity->pdistance = vect_mag(vect_sub(c->player->pos, entity->pos));
}

float find_target(core_t *c, entity_t *entity, sfVector2f target)
{
    float a = get_angle(entity->pos, target);
    float diff;
    float t_diff;

    diff = a - entity->angle;
    if (diff > 180)
        diff = (a - 360) - entity->angle;
    else if (diff < -180)
        diff = (a + 360) - entity->angle;
    clamp(-40, 40, diff);
    t_diff = diff;
    diff *= 0.05;
    if (diff > 0)
        entity->angle += (diff * diff * diff) + 0.5;
    if (diff < 0) {
        diff *= -1;
        entity->angle -= (diff * diff * diff) + 0.5;
    }
    entity->angle = sfSprite_getRotation(entity->w_sprite);
    return t_diff;
}
