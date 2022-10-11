/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** draw.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

void draw_entities2d(core_t *c)
{
    entity_t *tmp = c->entities;

    while (tmp != NULL) {
        sfRenderWindow_drawSprite(c->render.window, tmp->m_sprite, NULL);
        sfRenderWindow_drawRectangleShape(c->render.window, tmp->hitbox, NULL);
        tmp = tmp->next;
    }
}

void draw_grid(core_t *c)
{
    for (int i = 0; i < c->level.dim.y; i++)
        for (int j = 0; j < c->level.dim.x; j++)
            sfRenderWindow_drawRectangleShape(c->render.window,
            c->level.gridc[i][j]->shape, NULL);
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
    draw_entities2d(c);
    sfRenderWindow_setView(c->render.window, c->render3d.view);
}

void draw_walls(core_t *c)
{
    wall3d_t *tmp = c->render3d.walls;

    while (tmp != NULL) {
        sfRenderTexture_drawRectangleShape(c->render3d.rs_render, tmp->section, NULL);
        tmp = tmp->next;
    }
}

void draw_entities3d(core_t *c)
{
    entity_t *entity = c->entities;

    while (entity != NULL) {
        if (!entity->player)
            draw_entity3d(c, entity);
        entity = entity->next;
    }
}

void draw_background(core_t *c)
{
    sfRenderWindow_drawRectangleShape(c->render.window, c->ui.b1, NULL);
}

void draw_floor_ceiling(core_t *c)
{
    for (int i = 0; i < c->render.r_size.x; i++) {
        for (int j = 0; j < c->render.r_size.y; j++) {
            c->render3d.fc_buffer[i][j].color = sfWhite;
        }
        sfVertexBuffer_update(c->render3d.buffer, c->render3d.fc_buffer[i],
        c->render.r_size.y, c->render.r_size.y * i);
    }
    sfRenderTexture_drawVertexBuffer(c->render3d.rs_render,
    c->render3d.buffer, NULL);
}

void draw_3d(core_t *c)
{
    sfRenderTexture_clear(c->render3d.rs_render, sfBlack);
    sfRenderWindow_setView(c->render.window, c->render3d.view);
    //apply_bobbing(c, true);
    vrect_draw(NULL, c->render3d.rs_render, c->render3d.sky);
    vrect_draw(NULL, c->render3d.rs_render, c->render3d.ground);
    //draw_floor_ceiling(c);
    draw_walls(c);
    draw_entities3d(c);

    del_walls(c);

    sfRenderTexture_display(c->render3d.rs_render);

    sfRectangleShape_setPosition(c->render3d.fs_renderer, sfView_getCenter(c->render3d.view));
    sfRectangleShape_setTexture(c->render3d.fs_renderer, sfRenderTexture_getTexture(c->render3d.rs_render), false);
    sfRenderWindow_drawRectangleShape(c->render.window, c->render3d.fs_renderer, NULL);
}

void draw_ui(core_t *c)
{
    sfRenderWindow_setView(c->render.window, c->ui.view);
    sfRenderWindow_drawText(c->render.window, c->render.fps_hint, NULL);
}

void draw_all(core_t *c)
{
    draw_3d(c);
    draw_2d(c);
    draw_ui(c);
}

void draw_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i] != NULL; i++) {
        if (c->ui.button[i]->scene == c->render.scene)
            sfRenderWindow_drawRectangleShape(c->render.window,
            c->ui.button[i]->shape, NULL);
    }
}

void draw_select_menu(core_t *c)
{
    draw_background(c);
    draw_buttons(c);
    sfRenderWindow_drawText(c->render.window, c->ui.level_selec_text, NULL);
}

void draw_main_menu(core_t *c)
{
    draw_background(c);
    draw_buttons(c);
}
