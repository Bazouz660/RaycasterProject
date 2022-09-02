/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** functions.c
*/

#include "my.h"

void on_click_play(core_t *c, button_t *button)
{
    c->render.scene = 1;
}

void on_click_exit(core_t *c, button_t *button)
{
    exit(0);
}

void on_click_next(core_t *c, button_t *button)
{
    if (c->ui.selected_level < c->render.nb_levels - 1)
        c->ui.selected_level++;
    sfText_setString(c->ui.level_selec_text,
    my_strcat(my_strcat(my_int_to_str(c->ui.selected_level + 1),
    " / "), my_int_to_str(c->render.nb_levels)));
}

void on_click_prev(core_t *c, button_t *button)
{
    if (c->ui.selected_level > 0)
        c->ui.selected_level--;
    sfText_setString(c->ui.level_selec_text,
    my_strcat(my_strcat(my_int_to_str(c->ui.selected_level + 1),
    " / "), my_int_to_str(c->render.nb_levels)));
}

void on_click_selec_lvl(core_t *c, button_t *button)
{
    load_level(c, c->level_models[c->ui.selected_level]);
    c->render.scene = 2;
    sfRenderWindow_setMouseCursorVisible(c->render.window, false);
}
