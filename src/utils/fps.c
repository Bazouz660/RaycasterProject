/*
** EPITECH PROJECT, 2021
** smoke test
** File description:
** fps.c
*/

#include "my.h"

float time_as_sec(sfTime time)
{
    return (time.microseconds/1000000.0);
}

float get_fps(sfClock *clock, sfTime *prev_time)
{
    float fps;
    sfTime currentTime;

    currentTime = sfClock_getElapsedTime(clock);
    fps = 1.0f / (time_as_sec(currentTime) - time_as_sec(*prev_time));
    *prev_time = currentTime;
    return fps;
}
