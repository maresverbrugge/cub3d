/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:30:55 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:30:56 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**free_2d_array(char **array_2d)
{
	size_t	i;

	i = 0;
	if (array_2d == NULL)
		return (NULL);
	while (array_2d[i])
		free(array_2d[i++]);
	free(array_2d);
	return (NULL);
}

void	free_all(t_cub3d *cub3d)
{
	if (cub3d->n_texture)
		mlx_delete_texture(cub3d->n_texture);
	if (cub3d->e_texture)
		mlx_delete_texture(cub3d->e_texture);
	if (cub3d->s_texture)
		mlx_delete_texture(cub3d->s_texture);
	if (cub3d->w_texture)
		mlx_delete_texture(cub3d->w_texture);
	if (cub3d->map)
		cub3d->map = free_2d_array(cub3d->map);
	if (cub3d->player)
		free(cub3d->player);
	if (cub3d->mm)
		free(cub3d->mm);
}
