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

bool	is_identifier(char *str)
{
	if (ft_strncmp(str, "C ", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "F ", 2) == 0)
		return (true);
	else if (ft_strncmp(str, "NO ", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "EA ", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "SO ", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "WE ", 3) == 0)
		return (true);
	return (false);
}

bool	is_double_colour(t_cub3d *cub3d, char identifier)
{
	if (identifier == 'C' && cub3d->ceiling_flag == true)
		return (true);
	if (identifier == 'F' && cub3d->floor_flag == true)
		return (true);
	return (false);
}

bool	is_double_texture_identifier(t_cub3d *cub3d, char *identifier)
{
	if (ft_strncmp(identifier, "NO ", 3) == 0 && cub3d->n_texture != NULL)
		return (true);
	if (ft_strncmp(identifier, "EA ", 3) == 0 && cub3d->e_texture != NULL)
		return (true);
	if (ft_strncmp(identifier, "SO ", 3) == 0 && cub3d->s_texture != NULL)
		return (true);
	if (ft_strncmp(identifier, "WE ", 3) == 0 && cub3d->w_texture != NULL)
		return (true);
	return (false);
}

bool	all_elements_provided(t_cub3d *cub3d)
{
	if (cub3d->n_texture == NULL || cub3d->e_texture == NULL
		|| cub3d->s_texture == NULL || cub3d->w_texture == NULL)
		return (false);
	if (cub3d->ceiling_flag == false || cub3d->floor_flag == false)
		return (false);
	return (true);
}
