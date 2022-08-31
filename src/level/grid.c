/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** grid.c
*/

#include "my.h"

grid_case_t *new_grid_case(int index, int type, sfVector2f pos,
sfVector2f size, int ix, int iy)
{
    grid_case_t *gcase = malloc(sizeof(grid_case_t));

    gcase->index = index;
    gcase->type = type;
    gcase->pos = pos;
    gcase->shape = sfRectangleShape_create();
    sfRectangleShape_setSize(gcase->shape, size);
    sfRectangleShape_setPosition(gcase->shape, pos);
    sfRectangleShape_setFillColor(gcase->shape, sfBlack);
    if (type == 1)
        sfRectangleShape_setFillColor(gcase->shape, sfWhite);
    if (type == 2)
        sfRectangleShape_setFillColor(gcase->shape, sfCyan);
    if (type == 3)
        sfRectangleShape_setFillColor(gcase->shape, sfBlue);
    if (type == 4)
        sfRectangleShape_setFillColor(gcase->shape, sfGreen);
    if (type == 5)
        sfRectangleShape_setFillColor(gcase->shape, sfYellow);
    sfRectangleShape_setOutlineColor(gcase->shape, (sfColor){200, 200, 200, 255});
    sfRectangleShape_setOutlineThickness(gcase->shape, 1);
    sfRectangleShape_setOrigin(gcase->shape, get_rect_center(gcase->shape));
    return gcase;
}
