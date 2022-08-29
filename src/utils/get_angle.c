/*
** EPITECH PROJECT, 2021
** ants
** File description:
** get_angle.c
*/

#include "my.h"

double rad_to_deg(double angle)
{
    double rad = 0;
    rad = angle * (180 / PI);
    return rad;
}

double deg_to_rad(double angle)
{
    double deg = 0;
    deg = angle * PI / 180;
    return deg;
}

double get_angle(sfVector2f v1, sfVector2f v2)
{
    double angle = atan2(v2.y - v1.y, v2.x - v1.x ) * (180 / PI);
    if (angle < 0)
        angle += 360;
    return angle;
}
