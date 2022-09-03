/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** clamp.c
*/

double clamp(double min, double max, double n)
{
    if (n > max)
        return max;
    if (n < min)
        return min;
    return n;
}
