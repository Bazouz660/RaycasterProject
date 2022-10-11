/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** creation.c
*/

#include "structs.h"
#include "includes.h"
#include "structs.h"
#include "prototypes.h"

static void set_attributes(entity_t *entity)
{
	sfSprite_setScale(entity->w_sprite, entity->scale);
	sfSprite_setOrigin(entity->w_sprite, get_sprite_center(entity->w_sprite));
	sfSprite_setPosition(entity->w_sprite, entity->pos);
	sfSprite_setRotation(entity->w_sprite, rad_to_deg(entity->angle));
	sfRectangleShape_setSize(entity->hitbox, (sfVector2f){40, 40});
	sfRectangleShape_setOrigin(entity->hitbox, get_rect_center(entity->hitbox));
	sfRectangleShape_setFillColor(entity->hitbox, TransparentRed);
	sfRectangleShape_setPosition(entity->hitbox, entity->pos);
}

static void define_attributes(entity_t *entity, sfVector2f pos)
{
	entity->angle = 0.01;
	entity->index = 0;
	entity->pos = pos;
	entity->vel = (sfVector2f){0, 0};
	entity->acceleration = 1;
	entity->acc = entity->vel;
	entity->angle_vel = 0;
	entity->sprint_speed = 1;
	entity->pdistance = 0;
	entity->screen_pos = (sfVector2f){0, 0};
	entity->dir = (sfVector2f){1, 0};
	entity->ref_dir = entity->dir;
	entity->base_scale = (sfVector2f){0.1, 0.1};
	entity->scale = entity->base_scale;
}

static void set_textures(entity_t *entity, int id, sfTexture **t_dictionary)
{
	if (id == 0) {
	    sfSprite_setTexture(entity->w_sprite,
	    sfTexture_createFromFile("assets/player/2dplayer.png", NULL), true);
		sfSprite_setColor(entity->w_sprite, sfBlue);
		entity->player = true;
	}
	if (id == 1) {
		sfSprite_setTexture(entity->w_sprite, t_dictionary[0], false);
		entity->player = false;
	}
}

entity_t *new_entity(core_t *c, sfVector2f pos, int id)
{
	entity_t *entity = malloc(sizeof(entity_t));

    define_attributes(entity, pos);
	entity->hitbox = sfRectangleShape_create();
	entity->w_sprite = sfSprite_create();
	set_textures(entity, id, c->textures.enemy);
	set_attributes(entity);
	entity->m_sprite = sfSprite_copy(entity->w_sprite);
	return entity;
}
