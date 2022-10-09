/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** draw.c
*/

#include "my.h"

void draw_entities2d(core_t *c)
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
    del_walls(c);
}

void draw_entity3d(core_t *c, entity_t *entity)
{
    sfVector2f h;
    sfVector2f screen_pos;
    sfVector2f scale;
    double player_angle = rad_to_deg(-c->player->angle);
    double distance = dist_from(entity->pos, c->player->pos);

    norm_deg(&player_angle, 0, 360);

    ////printf("\n\n===============================\n");

    //printf("player angle = %f\n", player_angle);

    h.x = entity->pos.x - c->player->pos.x;
    h.y = entity->pos.y - c->player->pos.y;
    double p = rad_to_deg(atan2(-h.y, h.x));
    norm_deg(&p, 0, 360);
    //printf("p = %f\n", p);
    double q = ((player_angle + (c->render3d.fov / 2))) - p;
    norm_deg(&q, 0, 360);
    //printf("q = %f\n", q);
    scale.x = 300.0f / distance;
    scale.x *= 0.2;
    scale.y = scale.x;
    screen_pos.x = q * (c->render.r_size.x / c->render3d.fov);
    //float c_angle = c->player->angle - ((sprite_screen.x / (float)c->render.w_size.x) * 360);
    //sprite_screen.x *= cos(c_angle);
    //printf("sprite_screen x = %f\n", screen_pos.x);
    screen_pos.y = (c->render.r_size.y / 2.0) + ((sfTexture_getSize(sfSprite_getTexture(entity->sprite)).y / 2) * scale.y);
    entity->screen_pos = screen_pos;
    sfSprite_setPosition(entity->sprite, (sfVector2f){screen_pos.x, screen_pos.y});
    sfSprite_setOrigin(entity->sprite, get_sprite_center(entity->sprite));
    sfSprite_setScale(entity->sprite, (sfVector2f){scale.x, scale.y});
    sfSprite_setColor(entity->sprite, smooth_color(sfBlack, sfWhite, distance / 1000.0f));

    //printf("entity->pdistance = %f\n", entity->pdistance);
    //printf("depth_buffer[x] = %f\n", c->render3d.depth_buffer[(int)clamp(0, c->render.r_size.x - 1, screen_pos.x)]);
    //printf("entity->screen_pos = %d\n", (int)entity->screen_pos.x);
    //printf("res = %d, %d\n", c->render.r_size.x, c->render.r_size.y);
    if ((entity->pdistance) < c->render3d.depth_buffer[(int)clamp(0, c->render.r_size.x - 1, screen_pos.x)])
        sfRenderTexture_drawSprite(c->render3d.rs_render, entity->sprite, NULL);
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

void apply_bobbing(core_t *c, bool enable)
{
    static float prev_time = 0;
    float bobbing_speed = 2;
    static bool do_head_bobbing = false;
    static short sign = 0;

    if (!enable)
        return;
    if (vect_mag(c->player->vel) > 0.1 ||
        (sfView_getCenter(c->render3d.view).y > c->render.r_size.y - 0.1
        && sfView_getCenter(c->render3d.view).y < c->render.r_size.y + 0.1)) {
        do_head_bobbing = true;
        c->render3d.bobbing_clock += 1;
    }
    sfView_setCenter(c->render3d.view,
    (sfVector2f){sfView_getCenter(c->render3d.view).x,
    ((sin(c->render3d.bobbing_clock * bobbing_speed * 0.1) *\
    vect_mag(c->player->vel) * (2.0 * ((float)c->render.r_size.x /\
    (float)SCREEN_WIDTH)))) + (c->render.r_size.y / 2)});
}

void draw_background(core_t *c)
{
    sfRenderWindow_drawRectangleShape(c->render.window, c->ui.b1, NULL);
}

void draw_3d(core_t *c)
{
    sfRenderTexture_clear(c->render3d.rs_render, sfBlack);
    sfRenderWindow_setView(c->render.window, c->render3d.view);
    apply_bobbing(c, true);
    vrect_draw(NULL, c->render3d.rs_render, c->render3d.sky);
    vrect_draw(NULL, c->render3d.rs_render, c->render3d.ground);
    draw_walls(c);
    draw_entities3d(c);

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
