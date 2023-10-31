/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:32:06 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:32:07 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
}

void	print_sdf(t_cub3d *cub3d)
{
	print_map(cub3d->map);
	printf("F: %d\n", cub3d->floor_colour);
	printf("C: %d\n\n", cub3d->ceiling_colour);
}
