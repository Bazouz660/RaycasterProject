/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** update.c
*/

#include "structs.h"
#include "prototypes.h"

int my_list_size(entity_t const *begin)
{
    int count = 0;

    while (begin != NULL) {
        begin = begin->next;
        count++;
    }
    return (count);
}

static entity_t *swap_elem(entity_t *elem1, entity_t *elem2)
{
    entity_t* tmp = elem2->next;

    elem2->next = elem1;
    elem1->next = tmp;
    return (elem2);
}

entity_t *alpha_comp(entity_t *elem1, entity_t *elem2, int *change)
{
    if (elem1->pdistance < elem2->pdistance) {
        *change = 1;
        return (swap_elem(elem1, elem2));
    }
    return (elem1);
}

entity_t *sort_sprites(entity_t **linked_files,
entity_t *(*cmp)())
{
    int change = 0;
    entity_t **tmp = linked_files;
    entity_t *elem1 = *linked_files;
    entity_t *elem2 = (*linked_files)->next;

    for (int i = 0; i < my_list_size(*linked_files); i++, tmp = &(*tmp)->next)
        for (int j = 0; j < my_list_size(*linked_files) - i - 1; j++) {
            elem1 = *tmp;
            elem2 = (*tmp)->next;
            *tmp = (*cmp)(elem1, elem2, &change);
        }
    if (change == 0)
        return (*linked_files);
    return (sort_sprites(linked_files, &(*cmp)));
}

void update_entities(core_t *c)
{
    entity_t *tmp = c->entities;

    while (tmp != NULL) {
        entity_reposition(c, tmp);
        if (tmp->player == true)
            cast_rays(c, tmp);
        tmp = tmp->next;
    }
    sort_sprites(&c->entities, &alpha_comp);
}
