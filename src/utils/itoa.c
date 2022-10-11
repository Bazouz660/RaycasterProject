/*
** EPITECH PROJECT, 2021
** smoke test
** File description:
** itoa.c
*/

#include "includes.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return i;
    for (i = 0; str[i] != '\0'; i++);
    return (i);
}

char *my_revstr(char *str)
{
    int i = 0;
    int l = my_strlen(str);
    char x;

    i = 0;
    l = my_strlen(str) - 1;
    while (i < l) {
        x = str[i];
        str[i] = str[l];
        str[l] = x;
        i = i + 1;
        l = l - 1;
    }
    return (str);
}

char *my_int_to_str(int nb)
{
    int i = 0;
    char *my_str;
    char sign = nb < 0 ? '-' : '+';

    if (nb == 0)
        return ("0");
    my_str = malloc(sizeof(char) * 12);
    nb = nb < 0 ? nb * -1 : nb;
    for (i; nb > 0; i++) {
        my_str[i] = nb % 10 + '0';
        nb /= 10;
    }
    if (sign == '-') {
        my_str[i] = sign;
        my_str[i + 1] = '\0';
    } else
        my_str[i] = '\0';
    my_revstr(my_str);
    return (my_str);
}
