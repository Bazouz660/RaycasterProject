/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** free_render.c
*/

#include "prototypes.h"

void free_render(core_t *c)
{
    sfText_destroy(c->render.fps_hint);
    sfView_destroy(c->render.view);
    sfRenderWindow_destroy(c->render.window);
    sfVertexBuffer_destroy(c->render3d.buffer);
    free(c->render3d.depth_buffer);
    for (int i = 0; i < c->render.r_size.x; i++)
        free(c->render3d.fc_buffer[i]);
    sfRectangleShape_destroy(c->render3d.fs_renderer);
    free(c->render3d.ground);
    free(c->render3d.sky);
    sfRenderTexture_destroy(c->render3d.rs_render);
    sfView_destroy(c->render3d.view);
    del_walls(c);
}
