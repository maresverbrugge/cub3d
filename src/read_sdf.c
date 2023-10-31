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

/*
** This function checks if the extension of the scene description file
** is '.cub'. If this is the case it returns 0, otherwise it returns -1.
*/

static int	check_extension(char *sdf)
{
	int	len;

	if (sdf == NULL)
		return (FAILURE);
	len = ft_strlen(sdf);
	if (len-- < 4)
		return (FAILURE);
	if (sdf[len--] != 'b')
		return (FAILURE);
	if (sdf[len--] != 'u')
		return (FAILURE);
	if (sdf[len--] != 'c')
		return (FAILURE);
	if (sdf[len--] != '.')
		return (FAILURE);
	return (SUCCESS);
}

int	open_sdf(char **argv)
{
	int		sdf_fd;

	if (check_extension(argv[1]) != SUCCESS)
		return (error_sdf("'.cub' expected"));
	sdf_fd = open(argv[1], O_RDONLY);
	if (sdf_fd < 0 || sdf_fd >= 1024)
		return (error(argv[1]));
	return (sdf_fd);
}

static char	*join_str(char *s1, char *s2)
{
	char	*joined;
	size_t	len_s1;
	size_t	len_s2;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		len_s1 = 0;
	else
		len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = malloc(len_s1 + len_s2 + 1);
	if (!joined)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ft_memmove(joined, s1, len_s1);
	ft_memmove(joined + len_s1, s2, len_s2);
	joined[len_s1 + len_s2] = '\0';
	free(s1);
	return (joined);
}

/*
** This function reads input from a file descriptor
** and writes it in one string.
** It returns 0 if the file has been read.
** It returns -1 if an error happened.
*/

int	file_to_str(int fd, char **file)
{
	int			result;
	static char	buf[BUFFER_SIZE + 1];

	if (BUFFER_SIZE <= 0)
		return (ft_putstr_fd("Error: invalid buffer size", 2), FAILURE);
	*file = NULL;
	result = 1;
	while (result > 0)
	{
		*file = join_str(*file, buf);
		if (*file == NULL)
			return (error("file_to_str: join_str"));
		result = read(fd, buf, BUFFER_SIZE);
		if (result == FAILURE)
			return (free(*file), error("file_to_str: read"));
		buf[result] = '\0';
	}
	return (SUCCESS);
}
