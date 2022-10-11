/*
** EPITECH PROJECT, 2021
** ants
** File description:
** get_angle.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

double rad_to_deg(double angle)
{
    double deg = 0;

    deg = angle * (180 / PI);
    return deg;
}

double deg_to_rad(double angle)
{
    double rad = 0;

    rad = angle * PI / 180;
    return rad;
}

double get_angle(sfVector2f v1, sfVector2f v2)
{
    double angle = atan2(v2.y - v1.y, v2.x - v1.x ) * (180 / PI);

    if (angle < 0)
        angle += 360;
    return angle;
}

int get_inv_angle(double angle)
{
    int res = angle + 180;

    res %= 360;
    return res;
}

double norm_deg(double *value, const double start, const double end)
{
  const double width = end - start;
  const double offsetValue = *value - start;

  *value = offsetValue - (floor(offsetValue / width) * width) + start;
  return *value;
}
