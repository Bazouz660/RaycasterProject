/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** smoothing.c
*/

#include "structs.h"

float lerp(float a, float b, float t)
{
    float res = a + (b - a) * t;

    return res;
}

sfVector2f lerp2f(sfVector2f a, sfVector2f b, float t)
{
    sfVector2f res;

    res.x = a.x + (b.x - a.x) * t;
    res.y = a.y + (b.y - a.y) * t;
    return res;
}
