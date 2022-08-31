/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** walls.c
*/

#include "my.h"

wall3d_t *new_section(ray_t ray, float view_height, int fov)
{
    wall3d_t *sec = malloc(sizeof(wall3d_t));
    float width = 3.2;
    float height = 100000;
    float left_pos = ((float)1920 * (float)((float)ray.index / fov));
    sfColor color;

    sec->section = sfRectangleShape_create();
    if (ray.type == 0) {
        sfRectangleShape_setSize(sec->section, (sfVector2f){0, 0});
        return sec;
    }
    sfRectangleShape_setSize(sec->section, (sfVector2f){width, height / ray.wall_dist});
    sfRectangleShape_setOrigin(sec->section, get_rect_center(sec->section));
    sfRectangleShape_setPosition(sec->section, (sfVector2f){left_pos, view_height});
    if (ray.type == 1)
        sfRectangleShape_setFillColor(sec->section, sfWhite);
    if (ray.type == 2)
        sfRectangleShape_setFillColor(sec->section, sfCyan);
    if (ray.type == 3)
        sfRectangleShape_setFillColor(sec->section, sfBlue);
    if (ray.type == 4)
        sfRectangleShape_setFillColor(sec->section, sfGreen);
    if (ray.type == 5)
        sfRectangleShape_setFillColor(sec->section, sfYellow);
    sfRectangleShape_setFillColor(sec->section, sfWhite);
    color = sfRectangleShape_getFillColor(sec->section);
    color = smooth_color(color, sfBlack, 100 / ray.wall_dist);
    if (ray.side == 1) {
        color.b = (float)color.b * 0.5;
        color.b < 0 ? color.b = 0 : 0;
        color.g = (float)color.g * 0.5;
        color.g < 0 ? color.g = 0 : 0;
        color.r = (float)color.r * 0.5;
        color.r < 0 ? color.r = 0 : 0;
    }
    sfRectangleShape_setFillColor(sec->section, color);
    return sec;
}

void add_wall(wall3d_t **head, ray_t ray, int fov)
{
	static int index = 0;
    int view_height = 540;
	wall3d_t *nnode = new_section(ray, view_height, fov);

	nnode->index = index;
	nnode->next = (*head);
	nnode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = nnode;
	(*head) = nnode;
	index++;
}

void del_wall(wall3d_t **head, wall3d_t *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
    sfRectangleShape_destroy(del_node->section);
	free(del_node);
}

void del_walls(core_t *c)
{
    wall3d_t *tmp = c->render3d.walls;

    while (tmp != NULL) {
        del_wall(&c->render3d.walls, tmp);
        tmp = tmp->next;
    }
}
