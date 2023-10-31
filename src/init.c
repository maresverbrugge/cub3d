/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:11 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:12 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mm(t_cub3d *cub3d)
{
	t_mini_map	*mm;

	mm = ft_calloc(1, sizeof(t_mini_map));
	if (!mm)
		return (error("init mini_map"), FAILURE);
	mm->max_width_points = map_max_width(cub3d->map);
	mm->max_height_points = map_max_height(cub3d->map);
	mm->x_interval = 10;
	mm->y_interval = 10;
	cub3d->mm = mm;
	return (SUCCESS);
}

int	init_cub3d(t_cub3d *cub3d)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (error("init cub3d->player"), FAILURE);
	cub3d->player = player;
	cub3d->mlx = NULL;
	cub3d->map = NULL;
	cub3d->mm = NULL;
	cub3d->ceiling_colour = 0;
	cub3d->floor_colour = 0;
	cub3d->n_texture = NULL;
	cub3d->e_texture = NULL;
	cub3d->s_texture = NULL;
	cub3d->w_texture = NULL;
	cub3d->contrast = 50;
	cub3d->ceiling_flag = false;
	cub3d->floor_flag = false;
	cub3d->mouse_x = -1;
	return (SUCCESS);
}

int	init_imgs(t_cub3d *cub3d)
{
	cub3d->mm->img = mlx_new_image(cub3d->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!cub3d->mm->img)
	{
		mlx_close_window(cub3d->mlx);
		return (error_mlx());
	}
	cub3d->player->img = mlx_new_image(cub3d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub3d->player->img)
	{
		mlx_delete_image(cub3d->mlx, cub3d->mm->img);
		mlx_close_window(cub3d->mlx);
		return (error_mlx());
	}
	return (SUCCESS);
}
