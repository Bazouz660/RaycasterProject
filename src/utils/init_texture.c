/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** init_texture.c
*/

#include "structs.h"

void init_animated_sprite(sfSprite *sprite, int columns, int rows)
{
    sfIntRect rect = sfSprite_getTextureRect(sprite);

    rect.left = 0;
    rect.top = 0;
    rect.width /= columns;
    rect.height /= rows;
    sfSprite_setTextureRect(sprite, rect);
}

int reset_anim(sfSprite *sprite)
{
    sfIntRect sheet_pos = sfSprite_getTextureRect(sprite);

    sheet_pos.top = 0;
    sheet_pos.left = 0;
    sfSprite_setTextureRect(sprite, sheet_pos);
    return 1;
}
