/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** free_entities.c
*/

#include "prototypes.h"

void free_entities(entity_t *list)
{
    entity_t *tmp = list;
    entity_t *tampon;

    while (tmp != NULL) {
        tampon = tmp->next;
        sfRectangleShape_destroy(tmp->hitbox);
        sfSprite_destroy(tmp->m_sprite);
        sfSprite_destroy(tmp->w_sprite);
        free(tmp);
        tmp = tampon;
    }
}
