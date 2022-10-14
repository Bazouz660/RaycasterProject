/*
** EPITECH PROJECT, 2022
** RaycasterProject
** File description:
** floor_cast.c
*/

#include "prototypes.h"

void cast_floor(core_t *c, sfTexture *texture)
{
    sfImage *floor_texture = sfImage_create(c->render.r_size.x, c->render.r_size.y);
    floor_texture = sfTexture_copyToImage(texture);
    double planeX = 0.0;
    double planeY = 0.70; //the 2d raycaster version of camera plane
    sfVector2u t_size = sfTexture_getSize(texture);

    float rayDirX0 = c->player->dir.x - planeX;
    float rayDirY0 = c->player->dir.y - planeY;
    float rayDirX1 = c->player->dir.x + planeX;
    float rayDirY1 = c->player->dir.y + planeY;

    //FLOOR CASTING
    for(int y = 0; y < c->render.r_size.y; y++)
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)

      // Current y position compared to the center of the screen (the horizon)
      int p = y - c->render.r_size.y / 2;

      // Vertical position of the camera.
      float posZ = 0.5 * c->render.r_size.y;

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      float rowDistance = posZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / c->render.r_size.x;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / c->render.r_size.x;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = (c->player->pos.x / 100.0) + rowDistance * rayDirX0;
      float floorY = (c->player->pos.y / 100.0) + rowDistance * rayDirY0;


      for(int x = 0; x < c->render.r_size.x; ++x)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        // get the texture coordinate from the fractional part
        int tx = (int)(t_size.x * (floorX - cellX)) & (t_size.x - 1);
        int ty = (int)(t_size.y * (floorY - cellY)) & (t_size.y - 1);

        floorX += floorStepX;
        floorY += floorStepY;

        // choose texture and draw the pixel
        int floorTexture = 3;
        int ceilingTexture = 6;
        sfColor color;

        // floor
        color = sfImage_getPixel(floor_texture, tx, ty);
        color = darken_color(color, c->render3d.farness_floor_buffer[x][y]);
        c->render3d.fc_buffer[x][y].color = color;

        //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        color = sfImage_getPixel(floor_texture, tx, ty);
        color = darken_color(color, c->render3d.farness_ceiling_buffer[x][y]);
        c->render3d.fc_buffer[x][c->render.r_size.y - y - 1].color = color;
      }
    }
    sfImage_destroy(floor_texture);
}