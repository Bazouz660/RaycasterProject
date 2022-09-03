/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** core.c
*/

#include "my.h"

void analyse_events(core_t *c)
{
    int mouse_released = 0;

    while (sfRenderWindow_pollEvent(c->render.window, &c->event)) {
        if (c->event.type == sfEvtMouseButtonReleased)
            mouse_released += 1;
        if (c->event.type == sfEvtClosed)
            sfRenderWindow_close(c->render.window);
        if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
            c->render.scene = 0;
            sfRenderWindow_setMouseCursorVisible(c->render.window, true);
        }
    }
    if (mouse_released > 0)
        c->ui.mouse_released = true;
    else
        c->ui.mouse_released = false;
}

void update_mouse(core_t *c)
{
    c->mouse.lastpos = c->mouse.pos;
    c->mouse.pos = get_mouse_pos_view(c);
    c->mouse.diff.x = c->mouse.pos.x - c->mouse.lastpos.x;
    c->mouse.diff.y = c->mouse.pos.y - c->mouse.lastpos.y;
}

void update_walls(core_t *c)
{
    c->render3d.floor_level = round(0.5f * c->render.w_size.x *\
    (1 + tan(c->render3d.vertical_angle)) / tan(0.5 * c->render3d.fov));
    c->render3d.ground->vertex[0].position.y = c->render.w_size.y - c->render3d.floor_level;
    c->render3d.ground->vertex[1].position.y = c->render.w_size.y - c->render3d.floor_level;
    c->render3d.sky->vertex[2].position.y = c->render.w_size.y - c->render3d.floor_level;
    c->render3d.sky->vertex[3].position.y = c->render.w_size.y - c->render3d.floor_level;
    for (int i = 0; i < c->render.nb_rays; i++)
        add_wall(c, &c->render3d.walls, c->render.rays[i], c->render3d.fov);
}

void loop_mouse_pos(core_t *c)
{
    if (c->mouse.pos.x >= sfRenderWindow_getSize(c->render.window).x - 1) {
        c->mouse.pos.x = 1;
        c->mouse.lastpos.x = 1;
        sfMouse_setPositionRenderWindow(c->mouse.pos, c->render.window);
    }
    if (c->mouse.pos.x - 1 < 0) {
        c->mouse.pos.x = sfRenderWindow_getSize(c->render.window).x;
        c->mouse.lastpos.x = c->mouse.pos.x;
        sfMouse_setPositionRenderWindow(c->mouse.pos, c->render.window);
    }
}

void render_game(core_t *c)
{
    loop_mouse_pos(c);
    update_entities(c);
    update_walls(c);
    draw_all(c);
}

void update_buttons(core_t *c)
{
    for (int i = 0; c->ui.button[i] != NULL; i++) {
        if (c->ui.button[i]->scene == c->render.scene)
            c->ui.button[i]->update(c, c->ui.button[i]);
    }
}

void render_menu(core_t *c)
{
    draw_main_menu(c);
    update_buttons(c);
}

void render_lvl_selec(core_t *c)
{
    draw_select_menu(c);
    update_buttons(c);
}

int game_loop(void)
{
    core_t *c = malloc(sizeof(core_t));
    float clock = 0;

    init_game(c);
    sfRenderWindow_setVerticalSyncEnabled(c->render.window, True);
    while (sfRenderWindow_isOpen(c->render.window)) {
        update_clock(c);
        if (c->clock.seconds > clock + 0.016) {
            clock = c->clock.seconds;
            update_fps(c);
            update_screen(c);
            update_mouse(c);
            if (c->render.scene == 0)
                render_menu(c);
            if (c->render.scene == 1)
                render_lvl_selec(c);
            if (c->render.scene == 2)
                render_game(c);
            analyse_events(c);
        }
    }
}

int main(int ac, char **av)
{
    return game_loop();
}
