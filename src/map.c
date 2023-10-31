/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:31:22 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:31:23 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** This function returns true if int c is 'N', 'E', 'S', 'W' , '1' or '0'
** else it returns false;
*/

static bool	is_map_char(int c)
{
	if (is_position_char(c) || c == '1' || c == '0')
		return (true);
	return (false);
}

static bool	is_surrounded(char **map, int x, int y)
{
	if (x == 0 || y == 0 || map[y + 1] == NULL)
		return (false);
	if ((int)(ft_strlen(map[y + 1])) < x)
		return (false);
	if (ft_isspace(map[y][x - 1]) || ft_isspace(map[y][x + 1])
			|| ft_isspace(map[y - 1][x]) || ft_isspace(map[y + 1][x]))
		return (false);
	return (true);
}

/*
** This function checks if the given x and y coordinate is one of the 7
** possible map characters ('1', '0', ' ', 'N', 'E', 'S', 'W').
** It also checks if the coordinate is surrounded by 
** one of the characters except the ' '.
*/

static int	is_valid_map_char(char **map, int x, int y)
{
	if (is_map_char(map[y][x]) == false)
	{
		if (map[y][x] != ' ')
			return (error_sdf("Invalid map: must be composed of only 7 \
possible characters ('1', '0', ' ', 'N', 'E', 'S', 'W')"));
	}
	if (map[y][x] == '0' || is_position_char(map[y][x]))
	{
		if (!is_surrounded(map, x, y))
			return (error_sdf("Invalid map: map must be \
closed/surrounded by walls"));
	}
	return (SUCCESS);
}

/*
** This function checks if the map is valid.
** A valid map consists of only '1', '0' and one of
** the following characters; 'N', 'E', 'S', 'W'.
** The map should be closed/surrounded by walls ('1's).
** Spaces (' ') can occur outside of the map.
** If the map is not valid an error is printed and -1 is returned.
** Returns 0 when the map is valid.
*/

int	validate_map(char **map)
{
	int	x;
	int	y;
	int	position_character;

	position_character = 0;
	y = 0;
	while (map[y] && position_character <= 1)
	{
		x = 0;
		while (map[y][x] && position_character <= 1)
		{
			if (is_identifier(map[y]) == true)
				return (error_sdf("provide only six valid type identifiers"), \
				FAILURE);
			if (is_position_char(map[y][x]))
				position_character++;
			if (is_valid_map_char(map, x, y) != SUCCESS)
				return (FAILURE);
			x++;
		}
		y++;
	}
	if (position_character != 1)
		return (error_sdf("Provide one position character"));
	return (SUCCESS);
}
