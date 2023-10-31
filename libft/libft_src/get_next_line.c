/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 16:31:53 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/03/09 15:54:49 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *to_read)
{
	char	*next_line;
	int		len;

	len = 0;
	if (to_read[len] == '\0')
		return (NULL);
	while (to_read[len] && to_read[len] != '\n')
		len++;
	if (to_read[len] == '\n')
		len++;
	next_line = gnl_substr(to_read, 0, len);
	return (next_line);
}

char	*split_line(char *to_read)
{
	int		len;
	char	*new_to_read;

	len = 0;
	while (to_read[len] && to_read[len] != '\n')
		len++;
	if (to_read[len] == '\n')
		len++;
	if (to_read[len] == '\0')
		return (free(to_read), NULL);
	new_to_read = gnl_strdup(&to_read[len]);
	return (free(to_read), new_to_read);
}

char	*read_file(int fd, char *to_read)
{
	int		bytes_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (to_read)
			free(to_read);
		return (NULL);
	}
	bytes_read = 1;
	while (!gnl_strchr(to_read, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(to_read), NULL);
		buffer[bytes_read] = '\0';
		to_read = gnl_strjoin(to_read, buffer);
	}
	return (free(buffer), to_read);
}

char	*get_next_line(int fd)
{
	static char	*to_read;
	char		*next_line;

	next_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	to_read = read_file(fd, to_read);
	if (!to_read)
		return (NULL);
	next_line = ft_get_line(to_read);
	to_read = split_line(to_read);
	if (!next_line && to_read)
	{
		free(to_read);
		to_read = NULL;
	}
	return (next_line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int 	fd;
// 	char	*s;

// 	fd = open("./files/textfile", O_RDONLY);
//     s = get_next_line(fd);
// 	printf("%s", s);
// 	free (s);
//     s = get_next_line(fd);
// 	printf("%s", s);
// 	free (s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free (s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free (s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free (s);
// 	s = get_next_line(fd);
// 	printf("%s", s);
// 	free (s);
// 	close(fd);
// 	return (0);
// }