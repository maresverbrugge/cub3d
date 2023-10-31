/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:52 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:36:41 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_ray_dir(int x, t_ray *ray, t_player *player)
{
	double	cam_x;

	cam_x = 2 * x / (double) SCREEN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * cam_x;
	ray->dir_y = player->dir_y + player->plane_y * cam_x;
}

static void	get_ray_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = INFINITY;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = INFINITY;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	get_ray_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}
/*
** Digital Differential Analysis is a fast algorithm typically used on square
** grids to find which squares a line hits
*/

static void	perform_dda(t_ray *ray, t_cub3d *cub3d)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub3d->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

int	get_line_height(int x, t_cub3d *cub3d, t_player *player, t_ray *ray)
{
	get_ray_dir(x, ray, player);
	ray->map_x = (int) player->pos_x;
	ray->map_y = (int) player->pos_y;
	get_ray_delta_dist(ray);
	get_ray_side_dist(ray, player);
	ray->hit = 0;
	perform_dda(ray, cub3d);
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	return ((int)(0.70 * SCREEN_HEIGHT / ray->perp_wall_dist));
}
