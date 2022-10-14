/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** cast.c
*/

#include "structs.h"
#include "prototypes.h"

static double get_wall_x(int side, float perpWallDist, sfVector2f r_pos, sfVector2f dir)
{
    double wallX;

    if (side == 0)
        wallX = r_pos.y + (perpWallDist) * dir.y;
    else
        wallX = r_pos.x + (perpWallDist) * dir.x;
    wallX -= floor((wallX));
    return wallX;
}

static void get_next_ray(core_t *c, ray_t *ray, float ray_projection_position)
{
    if (ray->index < c->render.r_size.x - 1) {
        float next_ray_direction = c->render3d.fov * (floor(0.5f * \
        c->render.r_size.x) - 1 - ray->index) / (c->render.r_size.x - 1);
        ray_projection_position = 0.5f * tan(deg_to_rad(next_ray_direction)) \
        / tan(deg_to_rad(0.5f * c->render3d.fov));
        ray->next_pos_x = (round(c->render.r_size.x * \
        (0.5f - ray_projection_position)));
    }
}

static void get_steps_size(sfVector2f dir, cast_t *cas)
{
    if (dir.x < 0) {
        cas->step.x = -1;
        cas->sideDist.x = (cas->r_pos.x - cas->map.x) * cas->deltaDist.x;
    } else {
        cas->step.x = 1;
        cas->sideDist.x = (cas->map.x + 1.0 - cas->r_pos.x) * cas->deltaDist.x;
    }
    if (dir.y < 0) {
        cas->step.y = -1;
        cas->sideDist.y = (cas->r_pos.y - cas->map.y) * cas->deltaDist.y;
    } else {
        cas->step.y = 1;
        cas->sideDist.y = (cas->map.y + 1.0 - cas->r_pos.y) * cas->deltaDist.y;
    }
}

static void perform_dda(core_t *c, cast_t *cas, ray_t *ray)
{
    while (cas->hit == 0) {
        if (cas->sideDist.x < cas->sideDist.y) {
          cas->sideDist.x += cas->deltaDist.x;
          cas->map.x += cas->step.x;
          cas->side = 0;
        } else {
          cas->sideDist.y += cas->deltaDist.y;
          cas->map.y += cas->step.y;
          cas->side = 1;
        }
        //if (vect_mag(cas->sideDist) * c->level.c_size.x > c->render.render_distance) {
        //    ray->wall_dist = -1;
        //    return;
        //}
        if (cas->map.x >= 0 && cas->map.x < c->level.dim.x && cas->map.y >= 0 &&
            cas->map.y < c->level.dim.y && c->level.gridc[cas->map.y]\
            [cas->map.x]->type > 0) {
            cas->hit = 1;
            ray->wall_index = (sfVector2u){cas->map.x, cas->map.y};
            ray->type = c->level.gridc[cas->map.y][cas->map.x]->type;
            cas->color = sfRectangleShape_getFillColor(c->level.gridc\
            [cas->map.y][cas->map.x]->shape);
        }
    }
}

static void store_depth_buffer(core_t *c, cast_t *cas, ray_t *ray)
{
    ray->wall_dist = (cas->perpWallDist * c->level.c_size.x);
    c->render3d.depth_buffer[ray->index] = ray->wall_dist;
    cas->ray_direction = c->render3d.fov * (floor(0.5f * c->render.r_size.x) \
    - ray->index) / (c->render.r_size.x - 1);
    cas->ray_projection_position = 0.5f * tan(deg_to_rad(cas->ray_direction)) \
    / tan(deg_to_rad(0.5f * c->render3d.fov));
    cas->current_column = (round(c->render.r_size.x * (0.5f - \
    cas->ray_projection_position)));
    ray->pos_x = cas->current_column;
    ray->next_pos_x = c->render.r_size.x;
}

static unsigned short fix_side_dir(core_t *c, cast_t *cas, ray_t *ray, sfVector2f start)
{
    if (cas->side == 0) {
        cas->perpWallDist = (cas->sideDist.x - cas->deltaDist.x);
    } else
        cas->perpWallDist = (cas->sideDist.y - cas->deltaDist.y);
    return 0;
}

static void init_struct(core_t *c, cast_t *cas, float maxlen,
sfVector2f dir, sfVector2f start)
{
    cas->dir = dir;
    cas->left = sfRectangleShape_getGlobalBounds(c->level.gridc[c->render.ray_pos.y][c->render.ray_pos.x]->shape).left;
    cas->top = sfRectangleShape_getGlobalBounds(c->level.gridc[c->render.ray_pos.y][c->render.ray_pos.x]->shape).top;
    cas->r_pos = (sfVector2f){start.x - cas->left, start.y - cas->top};
    cas->r_pos.x = (cas->r_pos.x / c->level.c_size.x) + c->render.ray_pos.x;
    cas->r_pos.y = (cas->r_pos.y / c->level.c_size.y) + c->render.ray_pos.y;
    cas->color = sfGreen;
    cas->map = (sfVector2i){(int)cas->r_pos.x, (int)cas->r_pos.y};
    cas->sideDist = (sfVector2f){0, 0};
    cas->deltaDist = (sfVector2f){(dir.x == 0) ? INFINITY : absolute(1 / dir.x),
    (dir.y == 0) ? INFINITY : absolute(1 / dir.y)};
    cas->perpWallDist = 0;
    cas->hit = 0;
    cas->maxlen = maxlen;
}

static sfColor determine_end(core_t *c, sfVector2f start, sfVector2f dir,
float maxlen, ray_t *ray)
{
    cast_t cas;
    int val = 0;

    init_struct(c, &cas, maxlen, dir, start);
    get_steps_size(dir, &cas);
    perform_dda(c, &cas, ray);
    if (ray->wall_dist == -1)
        return (sfColor){84, 84, 84, 84};
    ray->side = cas.side;
    val = fix_side_dir(c, &cas, ray, start);
    store_depth_buffer(c, &cas, ray);
    get_next_ray(c, ray, cas.ray_projection_position);
    ray->v2.position = vect_add(start, vect_mult(dir, cas.perpWallDist * c->level.c_size.x));
    ray->wall_x = get_wall_x(cas.side, cas.perpWallDist, cas.r_pos, dir);
    return cas.color;
}

ray_t new_ray(core_t *c, float p_angle, sfVector2f start, float maxlen,
sfVector2f refdir, float angle, int index)
{
    ray_t ray;
    matrix_t rot_mx = new_rot_matrix(angle);
    sfVector2f dir = multiply_vec(&rot_mx, refdir);
    float c_angle;
    sfColor color;

    ray.wall_index = (sfVector2u){0, 0};
    ray.v1.position = start;
    ray.index = index;
    if ((color = determine_end(c, start, dir, maxlen, &ray)).a == 84) {
        free_matrix(&rot_mx);
        return ray;
    }
    ray.v2.color = color;
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

    cast_floor(c, c->textures.wall[4]);
}
