/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** level_collision.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

void collision_response(entity_t *entity, sfFloatRect gb, sfFloatRect eb)
{
	if (gb.top > eb.top && gb.top + gb.height > eb.top + eb.height
		&& gb.left < eb.left + eb.width && gb.left + gb.width > eb.left) {
        entity->vel.y = 0;
        entity->pos.y = gb.top - eb.height / 2;
        return;
    } else if (eb.top > gb.top && eb.top + eb.height > gb.top + gb.height
		&& eb.left < gb.left + gb.width && eb.left + eb.width > gb.left) {
        entity->vel.y = 0;
        entity->pos.y = gb.top + gb.height + eb.height / 2;
        return;
    }
	if (eb.left < gb.left && eb.left + eb.width < gb.left + gb.width
		&& eb.top < gb.top + gb.height && eb.top + eb.height > gb.top) {
        entity->vel.x = 0;
        entity->pos.x = gb.left - eb.width / 2;
        return;
    } else if (eb.left > gb.left && eb.left + eb.width > gb.left + gb.width
		&& eb.top < gb.top + gb.height && eb.top + eb.height > gb.top) {
        entity->vel.x = 0;
        entity->pos.x = gb.left + gb.width + eb.width / 2;
        return;
    }
}

void check_level_collisions(core_t *c, level_t level, entity_t *entity)
{
    sfVector2f next_pos = vect_add(entity->pos, entity->vel);
    sfFloatRect gcase_b;
    sfFloatRect eb = sfRectangleShape_getGlobalBounds(entity->hitbox);
    sfFloatRect ebn = {eb.left + entity->vel.x, eb.top + entity->vel.y,
    eb.width, eb.height};
    int col = 0;

    for (int i = 0; i < level.dim.y; i++) {
        for (int j = 0; j < level.dim.x; j++) {
            gcase_b = sfRectangleShape_getGlobalBounds(level.gridc[i][j]->shape);
            if (level.gridc[i][j]->type == 0 && sfFloatRect_contains(&gcase_b,
                entity->pos.x, entity->pos.y)) {
                c->render.ray_pos = (sfVector2i){j, i};
                sfRectangleShape_setFillColor(level.gridc[i][j]->shape, sfRed);
            } else if (level.gridc[i][j]->type == 0)
                sfRectangleShape_setFillColor(level.gridc[i][j]->shape, sfBlack);
            if (level.gridc[i][j]->type != 0 && sfFloatRect_intersects(&gcase_b,
                &ebn, NULL)) {
                collision_response(entity, gcase_b, eb);
                col = 1;
            }
        }
    }
}
