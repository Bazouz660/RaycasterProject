/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** smooth_color.c
*/

#include "my.h"

sfColor smooth_color(sfColor c1, sfColor c2, double prog)
{
    float diff_r = c1.r - c2.r;
    float diff_g = c1.g - c2.g;
    float diff_b = c1.b - c2.b;
    float diff_a = c1.a - c2.a;
    sfColor res;

    if (prog > 1)
        prog = 1;
    if (prog < 0)
        prog = 0;
    res.r = c1.r + (diff_r * prog);
    res.g = c1.g + (diff_g * prog);
    res.b = c1.b + (diff_b * prog);
    res.a = c1.a + (diff_a * prog);
    return res;
}

sfColor darken_color(sfColor c1, double prog)
{
    sfColor res = c1;

    if (prog > 1)
        prog = 1;
    if (prog < 0)
        prog = 0;
    res.r = (float)c1.r * prog;
    res.g = (float)c1.g * prog;
    res.b = (float)c1.b * prog;
    return res;
}
