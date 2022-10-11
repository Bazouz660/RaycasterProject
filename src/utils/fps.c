/*
** EPITECH PROJECT, 2021
** smoke test
** File description:
** fps.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

float time_as_sec(sfTime time)
{
    return (time.microseconds/1000000.0);
}

float get_fps(sfClock *clock, sfTime *prev_time)
{
    float fps = 0;
    static int i = 0;
    sfTime currentTime;

    currentTime = sfClock_getElapsedTime(clock);
    if (i == 0) {
        *prev_time = currentTime;
        i++;
    }
    if ((time_as_sec(currentTime) - time_as_sec(*prev_time) == 0))
        return 0;
    fps = 1.0f / (time_as_sec(currentTime) - time_as_sec(*prev_time));
    *prev_time = currentTime;
    return fps;
}
