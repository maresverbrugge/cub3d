/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_start_position.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:01 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:02 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function finds the position character ('N', 'E', 'S' or 'W') in the map
** which represents the players starting position and
** stores that position as pos_x and pos_y in the cub3d structure.
** it returns the position character.
*/

static char	get_start_position(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (cub3d->map[y])
	{
		x = 0;
		while (cub3d->map[y][x])
		{
			if (is_position_char(cub3d->map[y][x]))
			{
				cub3d->player->pos_x = x + 0.5;
				cub3d->player->pos_y = y + 0.5;
				return (cub3d->map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
** This function stores the starting direction in the dir vector
** and the plane vector, which is perpendicular to the direction.
*/

static void	get_dir_and_plane(t_cub3d *cub3d, char position_character)
{
	if (position_character == 'N')
	{
		cub3d->player->dir_y = -1.0;
		cub3d->player->plane_x = 1.0;
	}
	if (position_character == 'E')
	{
		cub3d->player->dir_x = 1.0;
		cub3d->player->plane_y = 1.0;
	}
	if (position_character == 'S')
	{
		cub3d->player->dir_y = 1.0;
		cub3d->player->plane_x = -1.0;
	}
	if (position_character == 'W')
	{
		cub3d->player->dir_x = -1.0;
		cub3d->player->plane_y = -1.0;
	}
}

void	get_start_position_and_direction(t_cub3d *cub3d)
{
	char	position_character;

	position_character = get_start_position(cub3d);
	get_dir_and_plane(cub3d, position_character);
}
