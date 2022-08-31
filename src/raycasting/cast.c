/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** cast.c
*/

#include "my.h"

void rotate_point(sfVector2f center, float angle, sfVector2f *p)
{
    float s = sin(deg_to_rad(angle));
    float c = cos(deg_to_rad(angle));
    float xnew;
    float ynew;

    p->x -= center.x;
    p->y -= center.y;
    xnew = p->x * c - p->y * s;
    ynew = p->x * s + p->y * c;
    p->x = xnew + center.x;
    p->y = ynew + center.y;
}

sfColor determine_end(core_t *c, sfVector2f start, sfVector2f dir, float maxlen, ray_t *ray)
{
    float left = sfRectangleShape_getGlobalBounds(c->level.gridc[c->render.ray_pos.y][c->render.ray_pos.x]->shape).left;
    float top = sfRectangleShape_getGlobalBounds(c->level.gridc[c->render.ray_pos.y][c->render.ray_pos.x]->shape).top;
    sfVector2f r_pos = {start.x - left, start.y - top};
    r_pos.x = (r_pos.x / c->level.c_size.x) + c->render.ray_pos.x;
    r_pos.y = (r_pos.y / c->level.c_size.y) + c->render.ray_pos.y;
    sfColor color = sfGreen;
    sfVector2i map = {(int)r_pos.x, (int)r_pos.y};
    sfVector2f sideDist = {0, 0};
    sfVector2f deltaDist = {(dir.x == 0) ? INFINITY : absolute(1 / dir.x),
    (dir.y == 0) ? INFINITY : absolute(1 / dir.y)};
    double perpWallDist = 0;
    sfVector2i step;
    int hit = 0;
    int side;

    if (dir.x < 0) {
        step.x = -1;
        sideDist.x = (r_pos.x - map.x) * deltaDist.x;
    } else {
        step.x = 1;
        sideDist.x = (map.x + 1.0 - r_pos.x) * deltaDist.x;
    }
    if (dir.y < 0) {
        step.y = -1;
        sideDist.y = (r_pos.y - map.y) * deltaDist.y;
    } else {
        step.y = 1;
        sideDist.y = (map.y + 1.0 - r_pos.y) * deltaDist.y;
    }
    while (hit == 0) {
        if (sideDist.x < sideDist.y) {
          sideDist.x += deltaDist.x;
          map.x += step.x;
          side = 0;
        } else {
          sideDist.y += deltaDist.y;
          map.y += step.y;
          side = 1;
        }
        if (map.x >= 0 && map.x < c->level.dim.x && map.y >= 0 &&
            map.y < c->level.dim.y && c->level.gridc[map.y][map.x]->type > 0) {
            hit = 1;
            ray->type = c->level.gridc[map.y][map.x]->type;
            color = sfRectangleShape_getFillColor(c->level.gridc[map.y][map.x]->shape);
        }
    }
    ray->side = side;
    if (side == 0) {
        perpWallDist = (sideDist.x - deltaDist.x);
    } else {
        perpWallDist = (sideDist.y - deltaDist.y);
    }
    if (dir.x >= -0.00000001 && dir.x <= 0.00000001) {
        ray->v2.position = start;
        ray->wall_dist = -1;
        return sfBlack;
    }
    if (dir.y >= -0.00000001 && dir.y <= 0.00000001) {
        ray->v2.position = start;
        ray->wall_dist = -1;
        return sfBlack;
    }
    if ((perpWallDist * c->level.c_size.x) > maxlen) {
        perpWallDist = maxlen / c->level.c_size.x;
        ray->type = 0;
        ray->wall_dist = -1;
        color = sfBlack;
    }
    ray->wall_dist = perpWallDist * c->level.c_size.x;
    ray->v2.position = vect_add(start, vect_mult(dir, perpWallDist * c->level.c_size.x));
    return color;

}

ray_t new_ray(core_t *c, sfVector2f start, float maxlen, sfVector2f refdir, float angle, int index)
{
    ray_t ray;
    matrix_t rot_mx = new_rot_matrix(angle);
    sfVector2f dir = multiply_vec(&rot_mx, refdir);
    ray.v1.position = start;
    ray.v2.color = determine_end(c, start, dir, maxlen, &ray);
    ray.v1.color = ray.v2.color;
    ray.angle = angle;
    ray.index = index;
    free_matrix(&rot_mx);
    return ray;
}

void cast_rays(core_t *c, entity_t *src)
{
    c->render.nb_rays = 600;
    c->render.rays = NULL;
    c->render.rays = malloc(sizeof(ray_t) * (c->render.nb_rays + 1));
    for (int i = 0; i < c->render.nb_rays; i++) {
        c->render.rays[i] = new_ray(c, src->pos, c->render.render_distance,
        src->ref_dir, src->angle + ((DR / 10) * (i - c->render.nb_rays / 2)), i);
    }
}
