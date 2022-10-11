/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** set_sprite_pos.c
*/

#include "structs.h"

sfSprite *setSprite_pos(sfSprite *sprite, float posX, float posY)
{
    sfVector2f pos = {posX, posY};

    sfSprite_setPosition(sprite, pos);
    return (sprite);
}
