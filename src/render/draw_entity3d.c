/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** draw_entity3d.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

static double get_step_tex_x(const sfTexture *texture, float perc)
{
    int tex_size = sfTexture_getSize(texture).x;
    double texX = (perc * (double)tex_size);

    return texX;
}

static void split_and_draw(core_t *c, entity_t *entity, sfVector2f screen_pos,
sfVector2f scale)
{
    sfFloatRect bound = sfSprite_getGlobalBounds(entity->w_sprite);
    int nb_cols = bound.width;
    sfTexture *texture = (sfTexture *)sfSprite_getTexture(entity->w_sprite);
    sfVector2u t_size = sfTexture_getSize(texture);
    sfRectangleShape **sprite_sec;

    sprite_sec = malloc(sizeof(sfRectangleShape *) * (nb_cols + 1));
    sfSprite_setScale(entity->w_sprite, (sfVector2f){scale.x, scale.y});
    for (int i = 0; i < nb_cols; i++) {
        sprite_sec[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(sprite_sec[i], (sfVector2f){1, t_size.y});
        sfRectangleShape_setScale(sprite_sec[i], (sfVector2f){1, scale.y});
        sfRectangleShape_setTexture(sprite_sec[i], texture, false);
        sfRectangleShape_setTextureRect(sprite_sec[i],
        (sfIntRect){get_step_tex_x(texture,
        ((float)i / (float)nb_cols)), 0, 1, t_size.y});
        sfRectangleShape_setPosition(sprite_sec[i], (sfVector2f){screen_pos.x \
        + (i - (nb_cols / 2)), screen_pos.y - (bound.height / 2.0)});
        if ((entity->pdistance) < c->render3d.depth_buffer[(int)clamp(0,
            c->render.r_size.x - 1,
            (int)screen_pos.x + (i - (nb_cols / 2)) - 1)])
            sfRenderTexture_drawRectangleShape(c->render3d.rs_render,
            sprite_sec[i], NULL);
        sfRectangleShape_destroy(sprite_sec[i]);
    }
    free(sprite_sec);
}

void draw_entity3d(core_t *c, entity_t *entity)
{
    sfVector2f h = {entity->pos.x - c->player->pos.x,
    entity->pos.y - c->player->pos.y};
    sfVector2f s_pos;
    double player_angle = rad_to_deg(-c->player->angle);
    double distance = dist_from(entity->pos, c->player->pos);
    double p = rad_to_deg(atan2(-h.y, h.x));
    double q;
    sfVector2f scale = {(300.0f / entity->pdistance) * 0.2,
    (300.0f / entity->pdistance) * 0.2};

    norm_deg(&player_angle, 0, 360);
    norm_deg(&p, 0, 360);
    q = ((player_angle + (c->render3d.fov / 2))) - p;
    norm_deg(&q, 0, 360);
    s_pos.x = q * (c->render.r_size.x / c->render3d.fov);
    s_pos.y = (c->render.r_size.y / 2.0) + ((sfTexture_getSize\
    (sfSprite_getTexture(entity->w_sprite)).y / 2) * scale.y);
    entity->screen_pos = s_pos;
    sfSprite_setPosition(entity->w_sprite, (sfVector2f){s_pos.x, s_pos.y});
    sfSprite_setOrigin(entity->w_sprite, get_sprite_center(entity->w_sprite));
    sfSprite_setColor(entity->w_sprite, smooth_color(sfBlack,
    sfWhite, distance / 1000.0f));
    split_and_draw(c, entity, s_pos, scale);
}
