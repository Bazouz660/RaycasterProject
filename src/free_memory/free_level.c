/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** free_level.c
*/

#include "prototypes.h"

static void free_level_model(level_models_t *model)
{
    for (int i = 0; i < model->y; i++)
        free(model->matrix[i]);
}

void free_level(core_t *c)
{
    for (int i = 0; i < c->level.dim.y; i++) {
        for (int j = 0; j < c->level.dim.x; j++) {
            sfRectangleShape_destroy(c->level.gridc[i][j]->shape);
            free(c->level.gridc[i][j]);
        }
    }
    for (int i = 0; i < c->render.nb_levels; i++)
        free_level_model(&c->level_models[i]);
}
