/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** linked_list.c
*/

#include "structs.h"
#include "prototypes.h"

void add_entity(core_t *c, entity_t **head, sfVector2f pos, int id)
{
	static int index = 0;
	entity_t *nnode = new_entity(c, pos, id);

	nnode->index = index;
	nnode->next = (*head);
	nnode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = nnode;
	(*head) = nnode;
	index++;
}

void del_entity(entity_t **head, entity_t *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
    sfSprite_destroy(del_node->w_sprite);
	free(del_node);
}
