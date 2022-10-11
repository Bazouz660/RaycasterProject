/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** random_color.c
*/

#include "structs.h"
#include "prototypes.h"

sfColor random_color(void)
{
    sfColor color;

    color.r = random_number(0, 255);
    color.g = random_number(0, 255);
    color.b = random_number(0, 255);
    color.a = 255;
    return color;
}
