/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** v_rect.c
*/

#include "my.h"

vrect_t *vrect_create(void)
{
    vrect_t *vrect = malloc(sizeof(vrect_t));
    for (int i = 0; i < 4; i++) {
        vrect->vertex[i].position = (sfVector2f){0, 0};
        vrect->vertex[i].color = sfWhite;
        vrect->vertex[i].texCoords = (sfVector2f){0, 0};
    }
    vrect->pos = (sfVector2f){0, 0};
    vrect->origin = (sfVector2f){0, 0};
    vrect->size = (sfVector2f){0, 0};
    vrect->texture = NULL;
    vrect->color = sfWhite;
    return vrect;
}

void vrect_setsize(vrect_t *vrect, sfVector2f size)
{
    vrect->size = size;
    vrect->vertex[1].position.x = vrect->vertex[0].position.x + size.x;
    vrect->vertex[2].position = vect_add(vrect->vertex[0].position, size);
    vrect->vertex[3].position.y = vrect->vertex[0].position.y + size.y;
}

void vrect_setposition(vrect_t *vrect, sfVector2f position)
{
    vrect->pos = position;
    vrect->vertex[0].position = position;
    vrect->vertex[1].position = (sfVector2f){position.x + vrect->size.x,
    position.y};
    vrect->vertex[2].position = vect_add(vrect->vertex[0].position,
    vrect->size);
    vrect->vertex[3].position = (sfVector2f){position.x,
    position.y + vrect->size.y};
}

void vrect_settexture(vrect_t *vrect, sfTexture *texture)
{
    sfVector2u t_size =  sfTexture_getSize(texture);

    vrect->texture = texture;
    vrect->vertex[0].texCoords = (sfVector2f){0, 0};
    vrect->vertex[1].texCoords = (sfVector2f){t_size.x, 0};
    vrect->vertex[2].texCoords = (sfVector2f){t_size.x, t_size.y};
    vrect->vertex[3].texCoords = (sfVector2f){0, t_size.y};
}

void vrect_draw(sfRenderWindow *render_window, vrect_t *vrect)
{
    sfRenderStates render_states;

    render_states.blendMode = sfBlendAlpha;
    render_states.shader = NULL;
    render_states.transform = sfTransform_Identity;
    render_states.texture = vrect->texture;
    sfRenderWindow_drawPrimitives(render_window, vrect->vertex, 4,
    sfQuads, &render_states);
}

void vrect_setcolor(vrect_t *vrect, sfColor color, unsigned int side,
bool all_sides)
{
    if (side > 3)
        side = 3;
    vrect->vertex[side].color = color;
    if (all_sides <= 0)
        return;
    vrect->vertex[0].color = color;
    vrect->vertex[1].color = color;
    vrect->vertex[2].color = color;
    vrect->vertex[3].color = color;
}
