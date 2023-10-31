/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 11:33:46 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/03/09 15:53:21 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
{
	char	ch;

	if (!s)
		return (NULL);
	ch = c;
	while (*s != ch)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *) s);
}

char	*gnl_strcpy(char *dst, const char *src, size_t n)
{
	if (!dst || !src)
		return (NULL);
	while (n-- > 0)
		*dst++ = *src++;
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*re;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = gnl_strdup("");
	if (!s1)
		return (NULL);
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	re = malloc(len1 + len2 + 1);
	if (!re)
		return (free(s1), NULL);
	gnl_strcpy(re, s1, len1);
	gnl_strcpy(&(re[len1]), s2, len2 + 1);
	return (free(s1), re);
}

char	*gnl_strdup(char *s1)
{
	size_t	len;
	char	*s2;

	if (!s1)
		return (NULL);
	len = 0;
	while (s1[len])
		len++;
	s2 = malloc(len + 1);
	if (!s2)
		return (NULL);
	gnl_strcpy(s2, s1, len);
	s2[len] = '\0';
	return (s2);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	gnl_strcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
