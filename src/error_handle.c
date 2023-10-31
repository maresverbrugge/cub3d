/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handle.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:30:48 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/04 14:19:45 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_mlx(void)
{
	ft_putendl_fd(strerror(mlx_errno), 2);
	return (FAILURE);
}

int	error_mlx_load_png(char *identifier)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = 0;
	i = 0;
	while (identifier[i++] == ' ')
		start++;
	while (identifier[i++] != '\n')
		end++;
	write(2, "path_to_texture: \"", 19);
	write(2, &identifier[start], end + 1);
	write(2, "\"\n", 2);
	return (FAILURE);
}

int	error_sdf(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("Invalid scene description file: ", 2);
	ft_putendl_fd(msg, 2);
	return (FAILURE);
}

int	error(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	perror(msg);
	return (FAILURE);
}
