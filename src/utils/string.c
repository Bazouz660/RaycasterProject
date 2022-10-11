/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** string.c
*/

#include "includes.h"
#include "prototypes.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}

char *my_strdup(char const *src)
{
    char *str = NULL;
    int i = 0;

    if (src == NULL)
        return NULL;
    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    for (; src[i] != '\0'; i++)
        str[i] = src[i];
    str[i] = '\0';
    return (str);
}

char *my_strndup(char const *src, int n)
{
    char *str = malloc(sizeof(char) * (n + 1));
    int i = 0;

    for (; src[i] != '\0' && i < n; i++)
        str[i] = src[i];
    str[i] = '\0';
    return (str);
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;


    if (s1 == NULL && s2 == NULL)
        return 0;
    if (s1 == NULL)
        return (-1);
    if (s2 == NULL)
        return (1);
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0' && s2[i] == '\0')
            return (0);
        i++;
    }
    if (s1[i] == '\0' || (s1[i] < s2[i] && s2[i] != '\0'))
        return (1);
    return (-1);
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;


    if (s1 == NULL && s2 == NULL)
        return 0;
    if (s1 == NULL)
        return (-1);
    if (s2 == NULL)
        return (1);
    while (s1[i] == s2[i]) {
        if ((s1[i] == '\0' && s2[i] == '\0') || i == n - 1)
            return (0);
        i++;
    }
    if (s1[i] == '\0' || (s1[i] < s2[i] && s2[i] != '\0'))
        return (1);
    return (-1);
}

char *rm_str_char(char **str, char *to_remove)
{
    char *tmp = *str;
    char *res = malloc(sizeof(char) * (my_strlen(tmp) + 1));
    int x = 0;
    int found = 0;

    for (int i = 0; tmp[i] != '\0'; i++) {
        found = 0;
        for (int z = 0; to_remove[z] != '\0'; z++)
            if (tmp[i] == to_remove[z]) {
                found = 1;
                break;
            }
        if (found == 0) {
            res[x] = tmp[i];
            x++;
        }
    }
    res[x] = '\0';
    free(tmp);
    return res;
}

char *str_keep_char(char **str, char *to_keep)
{
    char *tmp = *str;
    char *res = malloc(sizeof(char) * (my_strlen(tmp) + 1));
    int x = 0;
    int found = 0;

    for (int i = 0; tmp[i] != '\0'; i++) {
        for (int z = 0; to_keep[z] != '\0'; z++)
            if (tmp[i] == to_keep[z]) {
                res[x] = tmp[i];
                x++;
            }
    }
    res[x] = '\0';
    free(tmp);
    return res;
}
