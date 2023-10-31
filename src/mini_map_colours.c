/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_map_colours.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:27 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:28 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	get_darker(uint32_t colour, t_cub3d *cub3d)
{
	int	r;
	int	g;
	int	b;

	r = ((colour >> 24) & 0xFF) - cub3d->contrast;
	g = ((colour >> 16) & 0xFF) - cub3d->contrast;
	b = ((colour >> 8) & 0xFF) - cub3d->contrast;
	if (r < 0)
		r += 255;
	if (g < 0)
		g += 255;
	if (b < 0)
		b += 255;
	return (rgba_to_colour(r, g, b, 255));
}

static uint32_t	get_lighter(uint32_t colour, t_cub3d *cub3d)
{
	int	r;
	int	g;
	int	b;

	r = ((colour >> 24) & 0xFF) + cub3d->contrast;
	g = ((colour >> 16) & 0xFF) + cub3d->contrast;
	b = ((colour >> 8) & 0xFF) + cub3d->contrast;
	if (r > 255)
		r -= 255;
	if (g > 255)
		g -= 255;
	if (b > 255)
		b -= 255;
	return (rgba_to_colour(r, g, b, 255));
}

uint32_t	get_colour_mm(char **map, int x, int y, t_cub3d *cub3d)
{
	uint32_t	wall_colour;

	wall_colour = get_darker(cub3d->floor_colour, cub3d);
	if (y < 0 || y >= cub3d->mm->max_height_points)
		return (wall_colour);
	else if (x > (int)(ft_strlen(map[y])))
		return (wall_colour);
	else if (y == (int)(cub3d->player->pos_y)
			&& x == (int)(cub3d->player->pos_x))
		return (get_lighter(cub3d->floor_colour, cub3d));
	else if (map[y][x] == '0' || is_position_char(map[y][x]))
		return (cub3d->floor_colour);
	else if (map[y][x] == '1')
		return (wall_colour);
	else
		return (wall_colour);
}
