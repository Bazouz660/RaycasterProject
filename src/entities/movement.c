/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** movement.c
*/

#include "my.h"

void player_controller(core_t *c, entity_t *entity, bool *dampen)
{
    if (entity->player == true) {
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
        if (sfKeyboard_isKeyPressed(sfKeyLShift))
            entity->sprint_speed = 2;
        else
            entity->sprint_speed = 1;
    }
}

void find_dist_to_player(core_t *c, entity_t *entity)
{
    //sfVector2f start = entity->pos;
    //float left = sfRectangleShape_getGlobalBounds(c->level.gridc[c->render.ray_pos.y][c->render.ray_pos.x]->shape).left;
    //float top = sfRectangleShape_getGlobalBounds(c->level.gridc[c->render.ray_pos.y][c->render.ray_pos.x]->shape).top;
    //sfVector2f r_pos = {start.x - left, start.y - top};
    //r_pos.x = (r_pos.x / c->level.c_size.x) + c->render.ray_pos.x;
    //r_pos.y = (r_pos.y / c->level.c_size.y) + c->render.ray_pos.y;

    //entity->pdistance = ((c->player->pos.x - entity->pos.x) * \
    //(c->player->pos.x - entity->pos.x) + (c->player->pos.y - entity->pos.y) * \
    //(c->player->pos.y - entity->pos.y));

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
    if (diff > 40)
        diff = 40;
    if (diff < -40)
        diff = -40;
    t_diff = diff;
    diff *= 0.05;
    if (diff > 0)
        entity->angle += (diff * diff * diff) + 0.5;
    if (diff < 0) {
        diff *= -1;
        entity->angle -= (diff * diff * diff) + 0.5;
    }
    entity->angle = sfSprite_getRotation(entity->sprite);
    return t_diff;
}

void enemy_controller(core_t *c, entity_t *entity)
{
    if (entity->player)
        return;

    //entity->acc = vect_mult(entity->dir, entity->acceleration);
    //find_target(c, entity, c->player->pos);
}

void entity_reposition(core_t *c, entity_t *entity)
{
    float friction = 0.1;
    bool dampen = true;
    static float vertical_angle_vel = 0;
    matrix_t rot_mx = new_matrix(2, 2);

    entity->acc = (sfVector2f){0, 0};
    player_controller(c, entity, &dampen);
    enemy_controller(c, entity);
    entity->acc = vect_mult(vect_unit(entity->acc),
    (entity->acceleration * (0.2 * entity->sprint_speed)));
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
    //sfSprite_setRotation(entity->sprite, rad_to_deg(entity->angle));
    sfRectangleShape_setPosition(entity->hitbox, entity->pos);
    find_dist_to_player(c, entity);
    free_matrix(&rot_mx);
}
