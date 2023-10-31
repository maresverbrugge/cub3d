/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:32 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:33 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_max_width(char **map)
{
	int	y;
	int	x;
	int	x_largest;

	x_largest = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > x_largest)
			x_largest = x;
		y++;
	}
	return (x_largest);
}

int	map_max_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

int	check_y(int y_player, t_mini_map *mm)
{
	if (y_player < MINIMAP_CENTRE)
		return (0);
	else if (y_player > (mm->max_height_points - MINIMAP_CENTRE))
		return (mm->max_height_points - MINIMAP_TILES);
	else
		return (y_player - MINIMAP_CENTRE);
}

int	check_x(int x_player, t_mini_map *mm)
{
	if (x_player < MINIMAP_CENTRE)
		return (0);
	else if (x_player > (mm->max_width_points - MINIMAP_CENTRE))
		return (mm->max_width_points - MINIMAP_TILES);
	else
		return (x_player - MINIMAP_CENTRE);
}

void	draw_mini_map(t_cub3d *cub3d, t_mini_map *mm)
{
	mm->y = 0;
	mm->y_hold = 0;
	mm->y2 = check_y(cub3d->player->pos_y, mm);
	while (mm->y < MINIMAP_HEIGHT)
	{
		mm->y_hold += mm->y_interval;
		while (mm->y < mm->y_hold)
		{
			mm->x = 0;
			mm->x2 = check_x(cub3d->player->pos_x, mm);
			mm->x_hold = 0;
			while (mm->x < MINIMAP_WIDTH)
			{
				mm->x_hold += mm->x_interval;
				while (mm->x < mm->x_hold)
					mlx_put_pixel(mm->img, mm->x++, mm->y,
						get_colour_mm(cub3d->map, mm->x2, mm->y2, cub3d));
				mm->x2++;
			}
			mm->y++;
		}
		mm->y2++;
	}
}
