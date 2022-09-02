/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** create.c
*/

#include "my.h"

button_t *button_create(sfTexture *texture, sfVector2f size, sfVector2f pos)
{
    static int index = 0;
    button_t *button = malloc(sizeof(button_t));
    sfVector2u t_size = sfTexture_getSize(texture);
    sfIntRect rect = {0, 0, t_size.x / 3, t_size.y};

    button->index = index;
    button->state = 0;
    button->visible = true;
    button->texture = texture;
    button->on_click = NULL;
    button->shape = sfRectangleShape_create();
    sfRectangleShape_setSize(button->shape, size);
    sfRectangleShape_setOrigin(button->shape, get_rect_center(button->shape));
    sfRectangleShape_setPosition(button->shape, pos);
    sfRectangleShape_setFillColor(button->shape, sfWhite);
    sfRectangleShape_setTexture(button->shape, button->texture, false);
    sfRectangleShape_setTextureRect(button->shape, rect);
    return button;
}

static void update(core_t *c, button_t *button)
{
    sfFloatRect bound = sfRectangleShape_getGlobalBounds(button->shape);
    sfIntRect t_rect = sfRectangleShape_getTextureRect(button->shape);
    sfVector2u t_size = sfTexture_getSize(sfRectangleShape_getTexture(button->shape));

    if (sfFloatRect_contains(&bound, c->mouse.pos.x, c->mouse.pos.y)) {
        if (button->state == 2 && c->ui.mouse_released == true)
            button->on_click(c, button);
        if (button->state == 0) {
            button->state = 1;
            t_rect.left = t_size.x / 3;
        }
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            button->state = 2;
            t_rect.left = t_size.x / 1.5;
        }
    } else if (button->state != 0) {
        button->state = 0;
        t_rect.left = 0;
    }
    sfRectangleShape_setTextureRect(button->shape, t_rect);
}

void button_set_update(button_t *button)
{
    button->update = &update;
}

void button_set_onclick(button_t *button, void(*func)(core_t *, button_t *))
{
    button->on_click = func;
}
