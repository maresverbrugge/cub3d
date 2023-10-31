/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:30:29 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:30:34 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	rgba_to_colour(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	get_r_g_or_b(char *sdf_str, int *i)
{
	int	colour;

	skip_char(sdf_str, i, ' ');
	if (!ft_isdigit(sdf_str[*i]))
		return (FAILURE);
	colour = ft_atoi(&sdf_str[*i]);
	while (ft_isdigit(sdf_str[*i]))
		(*i)++;
	skip_char(sdf_str, i, ' ');
	return (colour);
}

void	set_colour_flag(t_cub3d *cub3d, char identifier)
{
	if (identifier == 'C')
		cub3d->ceiling_flag = true;
	if (identifier == 'F')
		cub3d->floor_flag = true;
}

int	get_colour(t_cub3d *cub3d, char *sdf_str, int *i)
{
	int		r;
	int		g;
	int		b;
	char	c;

	c = sdf_str[(*i)++];
	skip_char(sdf_str, i, ' ');
	r = get_r_g_or_b(sdf_str, i);
	if (sdf_str[(*i)++] != ',')
		return (FAILURE);
	g = get_r_g_or_b(sdf_str, i);
	if (sdf_str[(*i)++] != ',')
		return (FAILURE);
	b = get_r_g_or_b(sdf_str, i);
	skip_char(sdf_str, i, ' ');
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (FAILURE);
	if (c == 'C')
		cub3d->ceiling_colour = rgba_to_colour(r, g, b, 255);
	else if (c == 'F')
		cub3d->floor_colour = rgba_to_colour(r, g, b, 255);
	set_colour_flag(cub3d, c);
	return (SUCCESS);
}
