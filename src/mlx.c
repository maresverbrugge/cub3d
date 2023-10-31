/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:37 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:45:34 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_cub3d *cub3d)
{
	draw_player_view(cub3d, cub3d->player);
	draw_mini_map(cub3d, cub3d->mm);
}

void	end_mlx(t_cub3d *cub3d)
{
	if (cub3d->player->img != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->player->img);
	if (cub3d->mm->img != NULL)
		mlx_delete_image(cub3d->mlx, cub3d->mm->img);
	if (cub3d->mlx != NULL)
	{
		mlx_close_window(cub3d->mlx);
		mlx_terminate(cub3d->mlx);
	}
}

int	perform_mlx_stuff(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT,
			"Raycasting Rascals", false);
	if (!cub3d->mlx)
		return (error_mlx());
	if (init_imgs(cub3d) != SUCCESS)
		return (FAILURE);
	draw(cub3d);
	if ((mlx_image_to_window(cub3d->mlx, cub3d->player->img, 0, 0) < 0))
	{
		end_mlx(cub3d);
		return (error_mlx());
	}
	if ((mlx_image_to_window(cub3d->mlx, cub3d->mm->img, 10, 10) < 0))
	{
		end_mlx(cub3d);
		return (error_mlx());
	}
	mlx_put_string(cub3d->mlx, \
		"Have a beautiful day, you rock star!\n", 180, 10);
	hookers(cub3d);
	mlx_loop(cub3d->mlx);
	end_mlx(cub3d);
	return (SUCCESS);
}
