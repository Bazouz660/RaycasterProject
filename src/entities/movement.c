/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** movement.c
*/

#include "structs.h"
#include "prototypes.h"

static void apply_sprint(entity_t *entity)
{
    if (sfKeyboard_isKeyPressed(sfKeyLShift))
        entity->sprint_speed = 2;
    else
        entity->sprint_speed = 1;
}

static void player_controller(core_t *c, entity_t *entity, bool *dampen)
{
    if (!entity->player)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        entity->acc = vect_mult(entity->dir, entity->acceleration);
    } else if (sfKeyboard_isKeyPressed(sfKeyS))
        entity->acc = vect_mult(entity->dir, -entity->acceleration);
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        entity->acc = vect_add(entity->acc, vect_mult(vect_norm(entity->dir),
        -entity->acceleration));
    if (sfKeyboard_isKeyPressed(sfKeyD))
        entity->acc = vect_add(entity->acc, vect_mult(vect_norm(entity->dir),
        entity->acceleration));
    if (c->mouse.diff.x > 0) {
        *dampen = false;
        entity->angle_vel += (float)c->mouse.diff.x / 6000;
    } else if (c->mouse.diff.x < 0) {
        *dampen = false;
        entity->angle_vel += (float)c->mouse.diff.x / 6000;
    }
    apply_sprint(entity);
}

static void enemy_controller(core_t *c, entity_t *entity)
{
    if (entity->player)
        return;

    //entity->acc = vect_mult(entity->dir, entity->acceleration);
    //find_target(c, entity, c->player->pos);
}

void dampen_angle_vel(core_t *c, entity_t *entity, bool dampen)
{
    if (dampen)
        entity->angle_vel = lerp(0, entity->angle_vel,
        exp2(-10.0 * c->clock.frame_delta));
    else
        entity->angle_vel = lerp(0, entity->angle_vel,
        exp2(-10.0 * c->clock.frame_delta));
}

void entity_reposition(core_t *c, entity_t *entity)
{
    float friction = 0.1;
    bool dampen = true;
    matrix_t rot_mx = new_matrix(2, 2);

    entity->acc = (sfVector2f){0, 0};
    player_controller(c, entity, &dampen);
    enemy_controller(c, entity);
    entity->acc = vect_mult(vect_unit(entity->acc),
    (entity->acceleration * (0.2 * entity->sprint_speed)) *\
    c->clock.elapsed_time / 6.0);
    entity->vel = vect_add(entity->vel, entity->acc);
    entity->vel = lerp2f((sfVector2f){0, 0}, entity->vel,
    exp((-((1 - friction) * 7) * c->clock.frame_delta)));
    check_level_collisions(c, c->level, entity);
    entity->pos = vect_add(entity->pos, entity->vel);
    entity->angle += entity->angle_vel * c->clock.elapsed_time;
    dampen_angle_vel(c, entity, dampen);
    rot_mx = new_rot_matrix(entity->angle);
    entity->dir = multiply_vec(&rot_mx, entity->ref_dir);
    sfSprite_setPosition(entity->w_sprite, entity->pos);
    sfRectangleShape_setPosition(entity->hitbox, entity->pos);
    sfSprite_setPosition(entity->m_sprite, entity->pos);
    sfSprite_setRotation(entity->m_sprite, rad_to_deg(entity->angle));
    find_dist_to_player(c, entity);
    free_matrix(&rot_mx);
}
