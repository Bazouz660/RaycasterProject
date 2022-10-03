/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** cast.c
*/

#include "my.h"

sfColor determine_end(core_t *c, sfVector2f start, sfVector2f dir,
float maxlen, ray_t *ray)
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
            ray->wall_index = (sfVector2u){map.x, map.y};
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
    ray->wall_dist = (perpWallDist * c->level.c_size.x);
    c->render3d.depth_buffer[ray->index] = ray->wall_dist;
    float ray_direction = c->render3d.fov * (floor(0.5f * c->render.w_size.x) - ray->index) / (c->render.w_size.x - 1);
    float ray_projection_position = 0.5f * tan(deg_to_rad(ray_direction)) / tan(deg_to_rad(0.5f * c->render3d.fov));
    short current_column = (round(c->render.w_size.x * (0.5f - ray_projection_position)));

    ray->pos_x = current_column;

    ray->next_pos_x = c->render.w_size.x;

    if (ray->index < c->render.w_size.x - 1) {
        float next_ray_direction = c->render3d.fov * (floor(0.5f * \
        c->render.w_size.x) - 1 - ray->index) / (c->render.w_size.x - 1);
        ray_projection_position = 0.5f * tan(deg_to_rad(next_ray_direction)) / tan(deg_to_rad(0.5f * c->render3d.fov));
        ray->next_pos_x = (round(c->render.w_size.x * (0.5f - ray_projection_position)));
    }

    ray->v2.position = vect_add(start, vect_mult(dir, perpWallDist * c->level.c_size.x));

    double wallX;
    if (side == 0)
        wallX = r_pos.y + (perpWallDist) * dir.y;
    else
        wallX = r_pos.x + (perpWallDist) * dir.x;
    wallX -= floor((wallX));
    ray->wall_x = wallX;
    return color;
}

ray_t new_ray(core_t *c, float p_angle, sfVector2f start, float maxlen, sfVector2f refdir, float angle, int index)
{
    ray_t ray;
    matrix_t rot_mx = new_rot_matrix(angle);
    sfVector2f dir = multiply_vec(&rot_mx, refdir);
    float c_angle;
    ray.wall_index = (sfVector2u){0, 0};
    ray.v1.position = start;
    ray.index = index;
    ray.v2.color = determine_end(c, start, dir, maxlen, &ray);
    ray.v1.color = ray.v2.color;
    ray.angle = angle;
    c_angle = p_angle - angle;
    if (c_angle < 0)
        c_angle += 2 * PI;
    if (c_angle > 2 * PI)
        c_angle -= 2 * PI;
    ray.wall_dist *= cos(c_angle);
    ray.dir = dir;
    free_matrix(&rot_mx);
    return ray;
}

void cast_rays(core_t *c, entity_t *src)
{
    c->render.rays = NULL;
    c->render.rays = malloc(sizeof(ray_t) * (c->render.nb_rays + 1));
    for (int i = 0; i < c->render.nb_rays; i++) {
        c->render.rays[i] = new_ray(c, src->angle, src->pos,
        c->render.render_distance,
        src->ref_dir, src->angle + (DR * (((float)(i - c->render.nb_rays / 2) \
        / c->render.nb_rays) * (float)c->render3d.fov)), i);
    }
}
