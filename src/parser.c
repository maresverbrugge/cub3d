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

static int	save_texture(t_cub3d *cub3d, char *identifier, char *tex_name)
{
	mlx_texture_t	*texture;

	if (is_double_texture_identifier(cub3d, identifier) == false)
	{
		if (tex_name[0] == '\0')
			return (free(tex_name), error_sdf("NO/EA/SO/WE ./path_to_texture"));
		texture = mlx_load_png(tex_name);
		if (!texture)
			return (free(tex_name), error_mlx_load_png(&identifier[2]));
		free(tex_name);
		if (ft_strncmp(identifier, "NO ", 3) == 0)
			cub3d->n_texture = texture;
		else if (ft_strncmp(identifier, "EA ", 3) == 0)
			cub3d->e_texture = texture;
		else if (ft_strncmp(identifier, "SO ", 3) == 0)
			cub3d->s_texture = texture;
		else if (ft_strncmp(identifier, "WE ", 3) == 0)
			cub3d->w_texture = texture;
		else
			return (error_sdf("NO/EA/SO/WE ./path_to_texture"));
		return (SUCCESS);
	}
	return (error_sdf("don't provide double texture identifiers"));
}

static int	get_path_to_texture(t_cub3d *cub3d, char *sdf_str, int *i)
{
	char	*identifier;
	char	*texture;
	int		end_tex_name;

	identifier = &sdf_str[(*i)++];
	(*i)++;
	skip_char(sdf_str, i, ' ');
	end_tex_name = *i;
	while (!ft_isspace(sdf_str[end_tex_name]))
		end_tex_name++;
	texture = NULL;
	texture = ft_strndup(&sdf_str[*i], end_tex_name - *i);
	if (!texture)
		return (error("get_path_to_texture"));
	if (save_texture(cub3d, identifier, texture) == FAILURE)
		return (FAILURE);
	*i = end_tex_name;
	skip_char(sdf_str, i, ' ');
	if (sdf_str[*i] != '\n')
		return (error_sdf("NO/EA/SO/WE ./path_to_texture"));
	return (SUCCESS);
}

static int	get_textures_and_colours(t_cub3d *cub3d, char *sdf_str, int *i)
{
	if (sdf_str[*i] == 'C' || sdf_str[*i] == 'F')
	{
		if (is_double_colour(cub3d, sdf_str[*i]) == true)
			return (error_sdf("don't provide double floor or ceiling colours"));
		if (get_colour(cub3d, sdf_str, i) != SUCCESS)
			return (error_sdf("C/F [0-255],[0-255],[0-255]"));
	}
	else if (is_position_char(sdf_str[*i]) == true)
	{
		if (get_path_to_texture(cub3d, sdf_str, i) != SUCCESS)
			return (FAILURE);
	}
	skip_char(sdf_str, i, '\n');
	return (*i);
}

/*
** This function gets info about the path to the textures and the colors
** of the floor and ceiling from the 'scene description file string' and
** saves this data in the cub3d structure.
** on error it prints an error and returns -1.
** on succes it returns the index of where the map starts in the sdf_str.
** note: each element can be seperated by one or more newlines  ('\n'),
** the information in each element can be seperated by one or more spaces (' ').
*/

static int	look_for_textures_and_colours(t_cub3d *cub3d, char *sdf_str)
{
	int		i;
	int		n;

	i = 0;
	n = 6;
	while (n--)
	{
		skip_char(sdf_str, &i, '\n');
		skip_char(sdf_str, &i, ' ');
		if (is_identifier(&sdf_str[i]) == true)
		{
			if (get_textures_and_colours(cub3d, sdf_str, &i) == FAILURE)
				return (FAILURE);
		}
		else
			return (error_sdf("provide six valid type identifiers"));
	}
	skip_char(sdf_str, &i, '\n');
	return (i);
}

int	parser(char **argv, t_cub3d *cub3d)
{
	int		sdf_fd;
	char	*sdf_str;
	int		map_index;

	sdf_fd = open_sdf(argv);
	if (sdf_fd == FAILURE)
		return (FAILURE);
	if (file_to_str(sdf_fd, &sdf_str) != SUCCESS)
		return (close(sdf_fd), FAILURE);
	close(sdf_fd);
	map_index = look_for_textures_and_colours(cub3d, sdf_str);
	if (map_index == FAILURE)
		return (free(sdf_str), FAILURE);
	if (all_elements_provided(cub3d) == false)
		return (error_sdf("provide six different valid type identifiers"));
	cub3d->map = ft_split(&sdf_str[map_index], '\n');
	if (!cub3d->map)
		return (free(sdf_str), error("ft_split in parser"));
	free(sdf_str);
	if (validate_map(cub3d->map) != SUCCESS)
		return (FAILURE);
	get_start_position_and_direction(cub3d);
	return (SUCCESS);
}
