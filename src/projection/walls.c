/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** walls.c
*/

#include "structs.h"
#include "prototypes.h"

double get_step_tex_x(sfTexture *texture, ray_t *ray)
{
    int tex_size = sfTexture_getSize(texture).x;
    double texX = (ray->wall_x * (double)tex_size);

    return texX;
}

wall3d_t *new_section(core_t *c, sfTexture *texture, ray_t ray, float view_height, int fov)
{
    wall3d_t *sec = malloc(sizeof(*sec));
    float width = get_max(0, (ray.next_pos_x - ray.pos_x));
    float height = 116000 - (300 * (fov));
    sfVector2u t_size = sfTexture_getSize(texture);
    sfIntRect t_rect = {get_step_tex_x(texture, &ray), 0, 0, t_size.y};
    sfColor color;

    sec->section = sfRectangleShape_create();
    if (ray.type == 0) {
        sfRectangleShape_setSize(sec->section, (sfVector2f){0, 0});
        return sec;
    }
    height *= 0.2;
    sfRectangleShape_setSize(sec->section, (sfVector2f){width, height / ray.wall_dist});
    sfRectangleShape_setOrigin(sec->section, get_rect_center(sec->section));
    sfRectangleShape_setPosition(sec->section, (sfVector2f){ray.pos_x + (width / 2), c->render.r_size.y / 2.0});
    sfRectangleShape_setFillColor(sec->section, (sfColor){166 * 1.2,142 * 1.2,43 *1.2,255});
    color = sfRectangleShape_getFillColor(sec->section);
    color = darken_color(color, 300 / pow(ray.wall_dist, 1.1));
    if (ray.index < c->render.r_size.x * 0.5)
        color = darken_color(color, clamp(0.15, 1, pow((ray.index / ((float)c->render.r_size.x / 2.0)), 0.7)));
    else
        color = darken_color(color, clamp(0.15, 1, pow(1.0 - ((ray.index - (c->render.r_size.x * 0.5)) / (float)c->render.r_size.x), 1.7)));
    if (ray.side == 1)
        color = darken_color(color, 0.6);
    sfRectangleShape_setTexture(sec->section, texture, false);
    sfRectangleShape_setTextureRect(sec->section, t_rect);
    sfRectangleShape_setFillColor(sec->section, color);
    return sec;
}

void add_wall(core_t*c, wall3d_t **head, ray_t ray, int fov)
{
	static int index = 0;
    int view_height = 540;
	wall3d_t *nnode = new_section(c, c->textures.wall[ray.type - 1], ray, view_height, fov);

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
    wall3d_t *tampon;

    while (tmp != NULL) {
        tampon = tmp->next;
        del_wall(&c->render3d.walls, tmp);
        tmp = tampon;
    }
}
