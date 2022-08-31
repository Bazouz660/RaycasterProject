/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** draw.c
*/

#include "my.h"

void draw_entities(core_t *c)
{
    entity_t *tmp = c->entities;

    while (tmp != NULL) {
        sfRenderWindow_drawSprite(c->render.window, tmp->sprite, NULL);
        sfRenderWindow_drawRectangleShape(c->render.window, tmp->hitbox, NULL);
        tmp = tmp->next;
    }
}

void draw_grid(core_t *c)
{
    for (int i = 0; i < c->level.dim.y; i++) {
        for (int j = 0; j < c->level.dim.x; j++) {
            sfRenderWindow_drawRectangleShape(c->render.window,
            c->level.gridc[i][j]->shape, NULL);
        }
    }
}

void draw_rays(core_t *c)
{
    sfVertexArray *array = sfVertexArray_create();

    if (c->render.rays == NULL)
        return;
    for (int i = 0; i < c->render.nb_rays; i++) {
        sfVertexArray_append(array, c->render.rays[i].v1);
        sfVertexArray_append(array, c->render.rays[i].v2);
    }
    sfVertexArray_setPrimitiveType(array, sfLines);
    sfRenderWindow_drawVertexArray(c->render.window, array, NULL);
    sfVertexArray_destroy(array);
    free(c->render.rays);
}

void draw_2d(core_t *c)
{
    sfRenderWindow_setView(c->render.window, c->render.view);
    draw_grid(c);
    draw_rays(c);
    draw_entities(c);
}

void draw_walls(core_t *c)
{
    wall3d_t *tmp = c->render3d.walls;

    while (tmp != NULL) {
        sfRenderWindow_drawRectangleShape(c->render.window, tmp->section, NULL);
        tmp = tmp->next;
    }
}

void draw_3d(core_t *c)
{
    sfRenderWindow_setView(c->render.window, c->render3d.view);
    sfRenderWindow_drawRectangleShape(c->render.window, c->render3d.sky, NULL);
    draw_walls(c);
}

void draw_all(core_t *c)
{
    draw_3d(c);
    draw_2d(c);
}
