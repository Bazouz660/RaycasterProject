/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** get_sprite_center.c
*/

#include "structs.h"

sfVector2f get_sprite_center(sfSprite *sprite)
{
    sfVector2f origin;
    sfIntRect rect = sfSprite_getTextureRect(sprite);

    origin.x = rect.width / 2;
    origin.y = rect.height / 2;
    return origin;
}

sfVector2f get_rect_center(sfRectangleShape *rect)
{
    sfVector2f origin;
    sfFloatRect frect = sfRectangleShape_getGlobalBounds(rect);

    origin.x = frect.width / 2;
    origin.y = frect.height / 2;
    return origin;
}
