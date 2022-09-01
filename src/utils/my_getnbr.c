/*
** EPITECH PROJECT, 2021
** my_getnbr
** File description:
** my_getnbr
*/

int result32(long nb, int sign, int count)
{
    if (count > 10)
        return (0);
    else if (nb <= 2147483647) {
        nb *= sign;
        return ((int) nb);
    }
    return (0);
}

int my_getnbr(char const *str)
{
    int sign = 1;
    long nb = 0;
    int i = 0;
    int count = 0;
    while (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        count++;
        if (nb == 0)
            nb += str[i] - '0';
        else {
            nb *= 10;
            nb += str[i] - '0';
        }
        i++;
    }
    return (result32(nb, sign, count));
}
