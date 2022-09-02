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
    sfContextSettings settings;

    settings.antialiasingLevel = 8;
    settings.attributeFlags = 0;
    settings.depthBits = 0;
    settings.majorVersion = 4.6;
    settings.minorVersion = 0;
    settings.sRgbCapable = false;
    settings.stencilBits = 0;
    mode.bitsPerPixel = 32;
    mode.width = 1920;
    mode.height = 1080;
    Window = sfRenderWindow_create(mode, title, sfFullscreen | sfClose,
    &settings);
    return Window;
}
