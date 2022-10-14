/*
** EPITECH PROJECT, 2021
** B-MUL-200-STG-2-1-myrpg-basile.trebus-hamann
** File description:
** create_window.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

sfRenderWindow *create_window(char const *title, bool fullscreen)
{
    sfRenderWindow *window;
    sfVideoMode mode = sfVideoMode_getDesktopMode();
    sfContextSettings settings;

    ssize_t count = 0;

    const sfVideoMode *a_modes = sfVideoMode_getFullscreenModes(&count);

    for (int i = 0; i < count; i++) {
        printf("fullscreen mode %d :\n", i);
        printf("mode.width = %d, mode.height = %d\n", a_modes[i].width, a_modes[i].height);
        if (sfVideoMode_isValid(a_modes[i]))
            printf("is mode valid : true\n\n");
        else
            printf("is mode valid : false\n\n");
    }

    settings.antialiasingLevel = 8;
    settings.attributeFlags = 0;
    settings.depthBits = 0;
    settings.majorVersion = 4.6;
    settings.minorVersion = 0;
    settings.sRgbCapable = false;
    settings.stencilBits = 0;
    if (fullscreen) {
        window = sfRenderWindow_create(mode, title, sfFullscreen | sfResize
        | sfClose, &settings);
    } else
        window = sfRenderWindow_create(mode, title, sfResize | sfClose, &settings);
    return window;
}
