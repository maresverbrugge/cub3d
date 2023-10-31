/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:34:08 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/03/09 15:52:42 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*read_file(int fd, char *to_read);
char	*split_line(char *to_read);
char	*ft_get_line(char *to_read);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strcpy(char *dst, const char *src, size_t n);
char	*gnl_strdup(char *s1);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

#endif