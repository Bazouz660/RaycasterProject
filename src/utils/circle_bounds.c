/*
** EPITECH PROJECT, 2021
** ants (copie 1)
** File description:
** circle_bounds.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

sfBool circle_intersect(sfVector2f center, float radius, sfVector2f point)
{
    if (pow(point.x - center.x, 2) + pow(point.y - center.y,
        2) < pow(radius, 2))
        return sfTrue;
    return sfFalse;
}

sfBool circles_intersect(sfVector2f center, float radius,
sfVector2f center2, float radius2)
{
    if (dist_from(center, center2) < radius
       || dist_from(center, center2) < radius2)
        return sfTrue;
    return sfFalse;
}
