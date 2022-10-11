/*
** EPITECH PROJECT, 2022
** fiziks
** File description:
** matrix.c
*/

#include "structs.h"

matrix_t new_matrix(int rows, int cols)
{
    matrix_t matrix;

    matrix.cols = cols;
    matrix.rows = rows;
    matrix.data = malloc(sizeof(float **) * rows);
    for (int i = 0; i < rows; i++) {
        matrix.data[i] = malloc(sizeof(float *) * cols);
        for (int j = 0; j < cols; j++) {
            matrix.data[i][j] = 0;
        }
    }
    return matrix;
}

sfVector2f multiply_vec(matrix_t *mx, sfVector2f vec)
{
    sfVector2f result = {0, 0};

    result.x = mx->data[0][0] * vec.x + mx->data[0][1] * vec.y;
    result.y = mx->data[1][0] * vec.x + mx->data[1][1] * vec.y;
    return result;
}

matrix_t new_rot_matrix(float angle)
{
    matrix_t mx = new_matrix(2, 2);

    mx.data[0][0] = cos(angle);
    mx.data[0][1] = -sin(angle);
    mx.data[1][0] = sin(angle);
    mx.data[1][1] = cos(angle);
    return mx;
}

void free_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
        free(matrix->data[i]);
}
