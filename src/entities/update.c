/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** update.c
*/

#include "my.h"

void update_entities(core_t *c)
{
    entity_t *tmp = c->entities;

    while (tmp != NULL) {
        entity_reposition(c, tmp);
        if (tmp->player == true)
            cast_rays(c, tmp);
        tmp = tmp->next;
    }
}
