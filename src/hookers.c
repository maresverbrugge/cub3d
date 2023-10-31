/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hookers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:06 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:07 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	adjust_contrast(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_MINUS)
		cub3d->contrast--;
	if (keydata.key == MLX_KEY_EQUAL)
		cub3d->contrast++;
}

static void	cursor_hook(double xpos, double ypos, void *param)
{
	t_cub3d	*cub3d;
	int		x_shift;

	(void)(ypos);
	cub3d = (t_cub3d *) param;
	if (mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (cub3d->mouse_x == -1)
			cub3d->mouse_x = xpos;
		else
		{
			x_shift = xpos - cub3d->mouse_x;
			if (x_shift > 0)
				rotate_right(cub3d->player);
			else if (x_shift < 0)
				rotate_left(cub3d->player);
			cub3d->mouse_x = xpos;
			draw(cub3d);
		}
	}
}

static void	mouse_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *) param;
	(void) mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		cub3d->mouse_x = -1;
}

static void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *) param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
	if (keydata.action != MLX_RELEASE && (keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_D))
		move(keydata, cub3d, cub3d->player);
	if (keydata.action != MLX_RELEASE && (keydata.key == MLX_KEY_LEFT
			|| keydata.key == MLX_KEY_RIGHT))
		rotate(keydata, cub3d->player);
	if (keydata.action != MLX_RELEASE && (keydata.key == MLX_KEY_MINUS
			|| keydata.key == MLX_KEY_EQUAL))
		adjust_contrast(keydata, cub3d);
	draw(cub3d);
}

void	hookers(t_cub3d *cub3d)
{
	mlx_key_hook(cub3d->mlx, &keyhook, cub3d);
	mlx_cursor_hook(cub3d->mlx, &cursor_hook, cub3d);
	mlx_mouse_hook(cub3d->mlx, &mouse_hook, cub3d);
}
