/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:58 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:59 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROTATE_SPEED)
		- player->dir_y * sin(ROTATE_SPEED);
	player->dir_y = old_dir_x * sin(ROTATE_SPEED)
		+ player->dir_y * cos(ROTATE_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(ROTATE_SPEED)
		- player->plane_y * sin(ROTATE_SPEED);
	player->plane_y = old_plane_x * sin(ROTATE_SPEED)
		+ player->plane_y * cos(ROTATE_SPEED);
}

void	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-ROTATE_SPEED)
		- player->dir_y * sin(-ROTATE_SPEED);
	player->dir_y = old_dir_x * sin(-ROTATE_SPEED)
		+ player->dir_y * cos(-ROTATE_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-ROTATE_SPEED)
		- player->plane_y * sin(-ROTATE_SPEED);
	player->plane_y = old_plane_x * sin(-ROTATE_SPEED)
		+ player->plane_y * cos(-ROTATE_SPEED);
}

void	rotate(mlx_key_data_t keydata, t_player *player)
{
	if (keydata.key == MLX_KEY_LEFT)
		rotate_left(player);
	if (keydata.key == MLX_KEY_RIGHT)
		rotate_right(player);
}
