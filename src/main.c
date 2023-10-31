/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:25:57 by mverbrug      #+#    #+#                 */
/*   Updated: 2023/10/04 14:44:20 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cub3d(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc == 2 && argv[1] != NULL)
	{
		if (init_cub3d(&cub3d) != SUCCESS)
			return (FAILURE);
		if (parser(argv, &cub3d) != SUCCESS)
			return (free_all(&cub3d), FAILURE);
		if (init_mm(&cub3d) != SUCCESS)
			return (FAILURE);
		if (perform_mlx_stuff(&cub3d) != SUCCESS)
			return (free_all(&cub3d), end_mlx(&cub3d), FAILURE);
		free_all(&cub3d);
	}
	else
		ft_putendl_fd("Usage: ./cub3D [path_to_scene_description_file.cub]", 1);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	if (cub3d(argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
