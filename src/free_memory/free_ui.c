/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** free_ui.c
*/

#include "prototypes.h"

static void free_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i]; i++)
        button_destroy(c->ui.button[i]);
    free(c->ui.button);
}

void free_ui(core_t *c)
{
    sfRectangleShape_destroy(c->ui.b1);
    sfFont_destroy(c->ui.font);
    sfText_destroy(c->ui.level_selec_text);
    sfView_destroy(c->ui.view);
    free_buttons(c);
}
