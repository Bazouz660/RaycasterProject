/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** update.c
*/

#include "structs.h"

static void update_key(core_t *c, switch_key_t *key)
{
    key->update(c, key);
}

void update_toggleable_keys(core_t *c)
{
    for (int i = 0; c->events.keys.toggleable[i].index != -1; i++) {
        update_key(c, &c->events.keys.toggleable[i]);
    }
}