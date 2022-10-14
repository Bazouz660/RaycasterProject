/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** actions.c
*/

#include "prototypes.h"

void toggle_fullscreen(core_t *c, switch_key_t *key)
{
    c->render.fullscreen = key->state;
    sfRenderWindow_close(c->render.window);
    sfRenderWindow_destroy(c->render.window);
    c->render.window = create_window("Backrooms", key->state);
}
