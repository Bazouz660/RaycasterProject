/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** free_textures.c
*/

#include "prototypes.h"

void free_textures(core_t *c)
{
    for (int i = 0; c->textures.wall[i]; i++)
        sfTexture_destroy(c->textures.wall[i]);
}
