/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** create_window.c
*/

#include "my.h"

sfRenderWindow *create_window(char const *title)
{
    sfRenderWindow *Window;
    sfVideoMode mode = sfVideoMode_getDesktopMode();

    mode.bitsPerPixel = 32;
    mode.width = 1920;
    mode.height = 1080;
    Window = sfRenderWindow_create(mode, title, sfFullscreen | sfClose, NULL);
    return Window;
}
