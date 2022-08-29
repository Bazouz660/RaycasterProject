/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** view.c
*/

#include "my.h"

sfFloatRect view_bounds(sfView *view)
{
    sfVector2f center = sfView_getCenter(view);
    sfVector2f size = sfView_getSize(view);
    sfFloatRect rect;

    rect.width = size.x;
    rect.height  = size.y;
    rect.left = center.x - (size.x / 2);
    rect.top = center.y - (size.y / 2);
    return rect;
}

sfBool get_mouse_intersect_view(core_t *c, sfFloatRect to_check)
{
    sfVector2i mouse_pos0 = sfMouse_getPositionRenderWindow(c->render.window);
    sfVector2f mouse_pos = {mouse_pos0.x + view_bounds(c->render.view).left,
    mouse_pos0.y + view_bounds(c->render.view).top};
    int posX = to_check.left;
    int posY = to_check.top;
    int posX_offset = to_check.left + to_check.width;
    int posY_offset = to_check.top + to_check.height;

    if ((mouse_pos.x >= posX && mouse_pos.x <= posX_offset)
        && (mouse_pos.y >= posY && mouse_pos.y <= posY_offset))
        return sfTrue;
    else
        return sfFalse;
}

sfVector2f get_mouse_pos_view(core_t *c)
{
    sfVector2i mouse_pos0 = sfMouse_getPositionRenderWindow(c->render.window);
    sfVector2f mouse_pos;

    mouse_pos = sfRenderWindow_mapPixelToCoords(c->render.window,
    mouse_pos0, c->render.view);
    return mouse_pos;
}
