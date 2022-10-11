/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** view.c
*/

#include "structs.h"
#include "prototypes.h"

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
    sfVector2i mouse_pos = get_mouse_pos_view(c);
    int posX_offset = to_check.left + to_check.width;
    int posY_offset = to_check.top + to_check.height;
    sfVector2i pos = sfRenderWindow_mapCoordsToPixel(c->render.window,
    (sfVector2f){to_check.left, to_check.top}, sfRenderWindow_getView(c->render.window));
    sfVector2i pos_offset = sfRenderWindow_mapCoordsToPixel(c->render.window,
    (sfVector2f){posX_offset, posY_offset}, sfRenderWindow_getView(c->render.window));

    if ((mouse_pos.x >= pos.x && mouse_pos.x <= pos_offset.x)
        && (mouse_pos.y >= pos.y && mouse_pos.y <= pos_offset.y))
        return sfTrue;
    else
        return sfFalse;
}

sfVector2i get_mouse_pos_view(core_t *c)
{
    sfVector2i mouse_pos0 = sfMouse_getPositionRenderWindow(c->render.window);
    sfVector2f mouse_pos;

    mouse_pos = sfRenderWindow_mapPixelToCoords(c->render.window,
    mouse_pos0, c->render.view);
    return mouse_pos0;
}
