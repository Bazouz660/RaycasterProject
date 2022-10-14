/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** create.c
*/

#include "structs.h"

static void update_toggleable_key(core_t *c, switch_key_t *key)
{
    if (key_pressed(key->keycode) && key->state == false && key->can_press)
        key->state = true;
    else if (key_pressed(key->keycode) && key->state == true && key->can_press)
        key->state = false;
    if (!key_pressed(key->keycode))
        key->can_press = true;
    if (key->prev_state != key->state) {
        key->can_press = false;
        key->prev_state = key->state;
        key->do_action(c, key);
    }
}

void init_toggleable_key(switch_key_t *key, sfKeyCode keycode,
void(*action)(core_t *, switch_key_t *))
{
    static int index = 0;

    key->index = index;
    key->keycode = keycode;
    key->can_press = true;
    key->state = false;
    key->prev_state = false;
    key->do_action = action;
    key->update = &update_toggleable_key;
}
