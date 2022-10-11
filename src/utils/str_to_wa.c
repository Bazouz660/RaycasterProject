/*
** EPITECH PROJECT, 2022
** SpageGameRepo
** File description:
** str_to_wa.c
*/

#include "structs.h"
#include "prototypes.h"

short is_separator(char const c, char const *separators)
{
    for (int i = 0; separators[i] != '\0'; i++) {
        if (c == separators[i])
            return 1;
    }
    return 0;
}

int get_word_nb(const char *str, const char *separators)
{
    int nb = 0;
    short sep = 0;

    if (str == NULL || my_strlen(str) == 0)
        return nb;
    for (int i = 0; i < my_strlen(str); i++) {
        sep = 0;
        while (is_separator(str[i], separators) == 1) {
            i++;
            sep = 1;
        }
        nb += sep;
    }
    return nb + 1;
}

void *append_char(char **str, char c)
{
    char *tmp = my_strdup(*str);
    char *tmp2 = *str;
    int i = 0;

    free(tmp2);
    if (tmp2 == NULL) {
        tmp2 = malloc(sizeof(char) * 2);
        tmp2[0] = c;
        tmp2[1] = '\0';
    }
    tmp2 = malloc(sizeof(char) * my_strlen(tmp) + 2);
    for (; i < my_strlen(tmp); i++) {
        tmp2[i] = tmp[i];
    }
    tmp2[i] = c;
    tmp2[i + 1] = '\0';
    free(tmp);
    *str = my_strdup(tmp2);
}

char **strwar(const char *str, const char *separators)
{
    int nb = get_word_nb(str, separators);
    char **arr = malloc(sizeof(char *) * (nb));
    short sep = 0;
    char *buffer = NULL;
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        sep = 0;
        for (; is_separator(str[i], separators) == 1; i++)
            sep = 1;
        if (sep == 1) {
            i--;
            arr[index++] = my_strdup(buffer);
            free(buffer);
            buffer = NULL;
        } else
            append_char(&buffer, str[i]);
    }
    arr[nb - 1] = NULL;
    return arr;
}