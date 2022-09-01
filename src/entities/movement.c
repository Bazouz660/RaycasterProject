/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** movement.c
*/

#include "my.h"

void entity_reposition(core_t *c, entity_t *entity)
{
    float friction = 0.1;
    bool dampen = true;
    matrix_t rot_mx = new_matrix(2, 2);

    entity->acc = (sfVector2f){0, 0};
    if (entity->player == true) {
        if (sfKeyboard_isKeyPressed(sfKeyZ)) {
            entity->acc = vect_mult(entity->dir, entity->acceleration);
        } else if (sfKeyboard_isKeyPressed(sfKeyS))
            entity->acc = vect_mult(entity->dir, -entity->acceleration);
        if (sfKeyboard_isKeyPressed(sfKeyQ))
            entity->acc = vect_mult(vect_norm(entity->dir), -entity->acceleration);
        if (sfKeyboard_isKeyPressed(sfKeyD))
            entity->acc = vect_mult(vect_norm(entity->dir), entity->acceleration);
        if (c->mouse.diff.x > 0) {
            dampen = false;
            entity->angle_vel += (float)c->mouse.diff.x / 5000;
        } else if (c->mouse.diff.x < 0) {
            dampen = false;
            entity->angle_vel += (float)c->mouse.diff.x / 5000;
        }
    }
    entity->acc = vect_mult(vect_unit(entity->acc), entity->acceleration / 3);
    entity->vel = vect_add(entity->vel, entity->acc);
    entity->vel = vect_mult(entity->vel, 1 - friction);
    check_level_collisions(c, c->level, entity);
    entity->pos = vect_add(entity->pos, entity->vel);
    entity->angle += entity->angle_vel;
    if (dampen == true)
        entity->angle_vel *= 0.9;
    else
        entity->angle_vel *= 0.96;
    rot_mx = new_rot_matrix(entity->angle);
    entity->dir = multiply_vec(&rot_mx, entity->ref_dir);
    sfSprite_setPosition(entity->sprite, entity->pos);
    sfSprite_setRotation(entity->sprite, rad_to_deg(entity->angle));
    sfRectangleShape_setPosition(entity->hitbox, entity->pos);
    free_matrix(&rot_mx);
}
