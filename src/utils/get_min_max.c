/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** get_min_max.c
*/

float get_min(float a, float b)
{
    if (a > b)
        return b;
    return a;
}

float get_max(float a, float b)
{
    if (a < b)
        return b;
    return a;
}
