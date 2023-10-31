/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:42 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:43 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_cub3d *cub3d, t_player *player)
{
	if (cub3d->map[(int)(player->pos_y)][(int)(player->pos_x
			+ player->dir_x * MOVE_SPEED * 6)] != '1')
		cub3d->player->pos_x += player->dir_x * MOVE_SPEED;
	if (cub3d->map[(int)(player->pos_y + player->dir_y
			* MOVE_SPEED * 6)][(int)player->pos_x] != '1')
		cub3d->player->pos_y += player->dir_y * MOVE_SPEED;
}

static void	move_back(t_cub3d *cub3d, t_player *player)
{
	if (cub3d->map[(int)(player->pos_y)][(int)(player->pos_x
			- player->dir_x * MOVE_SPEED * 6)] != '1')
		cub3d->player->pos_x -= player->dir_x * MOVE_SPEED;
	if (cub3d->map[(int)(player->pos_y - player->dir_y
			* MOVE_SPEED * 6)][(int)player->pos_x] != '1')
		cub3d->player->pos_y -= player->dir_y * MOVE_SPEED;
}

static void	move_right(t_cub3d *cub3d, t_player *player)
{
	if (cub3d->map[(int)(player->pos_y)][(int)(player->pos_x
			+ player->plane_x * MOVE_SPEED * 6)] != '1')
		cub3d->player->pos_x += player->plane_x * MOVE_SPEED;
	if (cub3d->map[(int)(player->pos_y + player->plane_y
			* MOVE_SPEED * 6)][(int)player->pos_x] != '1')
		cub3d->player->pos_y += player->plane_y * MOVE_SPEED;
}

static void	move_left(t_cub3d *cub3d, t_player *player)
{
	if (cub3d->map[(int)(player->pos_y)][(int)(player->pos_x
			- player->plane_x * MOVE_SPEED * 6)] != '1')
		cub3d->player->pos_x -= player->plane_x * MOVE_SPEED;
	if (cub3d->map[(int)(player->pos_y - player->plane_y
			* MOVE_SPEED * 6)][(int)player->pos_x] != '1')
		cub3d->player->pos_y -= player->plane_y * MOVE_SPEED;
}

void	move(mlx_key_data_t keydata, t_cub3d *cub3d, t_player *player)
{
	if (keydata.key == MLX_KEY_W)
		move_forward(cub3d, player);
	if (keydata.key == MLX_KEY_S)
		move_back(cub3d, player);
	if (keydata.key == MLX_KEY_D)
		move_right(cub3d, player);
	if (keydata.key == MLX_KEY_A)
		move_left(cub3d, player);
}
