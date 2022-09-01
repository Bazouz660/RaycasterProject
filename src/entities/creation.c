/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** creation.c
*/

#include "my.h"

entity_t *new_entity(sfVector2f pos, int id)
{
	entity_t *entity = malloc(sizeof(entity_t));

	entity->angle = 0.01;
	entity->index = 0;
	entity->pos = pos;
	entity->vel = (sfVector2f){0, 0};
	entity->acceleration = 1;
	entity->acc = entity->vel;
	entity->angle_vel = 0;
	entity->dir = (sfVector2f){1, 0};
	entity->ref_dir = entity->dir;
	entity->hitbox = sfRectangleShape_create();
	entity->sprite = sfSprite_create();
	sfSprite_setTexture(entity->sprite,
	sfTexture_createFromFile("assets/player/2dplayer.png", NULL), true);
	entity->base_scale = (sfVector2f){0.1, 0.1};
	entity->scale = entity->base_scale;
	sfSprite_setScale(entity->sprite, entity->scale);
	sfSprite_setOrigin(entity->sprite, get_sprite_center(entity->sprite));
	sfSprite_setPosition(entity->sprite, entity->pos);
	sfSprite_setRotation(entity->sprite, rad_to_deg(entity->angle));
	sfRectangleShape_setSize(entity->hitbox, (sfVector2f){30, 30});
	sfRectangleShape_setOrigin(entity->hitbox, get_rect_center(entity->hitbox));
	sfRectangleShape_setFillColor(entity->hitbox, TransparentRed);
	sfRectangleShape_setPosition(entity->hitbox, entity->pos);
	if (id == 0) {
		sfSprite_setColor(entity->sprite, sfBlue);
	    entity->player = true;
	} else
	    entity->player = false;
	return entity;
}

void add_entity(entity_t **head, sfVector2f pos, int id)
{
	static int index = 0;
	entity_t *nnode = new_entity(pos, id);

	nnode->index = index;
	nnode->next = (*head);
	nnode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = nnode;
	(*head) = nnode;
	index++;
}

void del_entity(entity_t **head, entity_t *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
    sfSprite_destroy(del_node->sprite);
	free(del_node);
}
