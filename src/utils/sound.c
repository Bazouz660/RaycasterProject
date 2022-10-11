/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** new_sound.c
*/

#include "structs.h"
#include "prototypes.h"

sfSound *set_up_new_sound(sfSound *new_sound, const char *buffer_location)
{
    sfSoundBuffer *new_sound_buffer = sfSoundBuffer_createFromFile(buffer_location);

    new_sound = sfSound_create();
    sfSound_setBuffer(new_sound, new_sound_buffer);
    return (new_sound);
}

void modulate_sound(sfSound *sound)
{
    sfSound_setPitch(sound,
    ((float)random_number(75, 130) / 100));
}
