/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_view.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:47 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:48 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_ceiling(t_cub3d *cub3d, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < (SCREEN_HEIGHT / 2))
	{
		x = 0;
		while (x < (SCREEN_WIDTH))
		{
			mlx_put_pixel(player->img, x, y, cub3d->ceiling_colour);
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_cub3d *cub3d, t_player *player)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < (SCREEN_WIDTH))
		{
			mlx_put_pixel(player->img, x, y, cub3d->floor_colour);
			x++;
		}
		y++;
	}
}

static void	draw_walls(t_cub3d *cub3d, t_player *player)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		draw_vertical(x, cub3d, player);
		x++;
	}
}

void	draw_player_view(t_cub3d *cub3d, t_player *player)
{
	draw_ceiling(cub3d, player);
	draw_floor(cub3d, player);
	draw_walls(cub3d, player);
}
