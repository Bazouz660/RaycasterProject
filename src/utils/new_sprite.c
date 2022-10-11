/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** new_sprite.c
*/

#include "structs.h"

sfSprite *new_sprite(char *texture_name, float x, float y)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f sprite_scale = {x, y};
    sfTexture *sprite_texture = sfTexture_createFromFile(texture_name,
    sfFalse);

    sfTexture_setRepeated(sprite_texture, sfTrue);
    sfSprite_setTexture(sprite, sprite_texture, sfFalse);
    sfSprite_setScale(sprite, sprite_scale);
    return (sprite);
}
