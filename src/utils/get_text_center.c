/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** get_text_center.c
*/

#include "structs.h"

sfVector2f get_text_center(sfText *text)
{
    sfFloatRect rect = sfText_getGlobalBounds(text);
    sfVector2f center;

    center.x = rect.width / 2;
    center.y = rect.height / 2;
    return center;
}
