/*
** EPITECH PROJECT, 2022
** SpaceGame
** File description:
** absolute.c
*/

double absolute(double value)
{
    if (value < 0)
        value *= -1;
    return value;
}
