/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:32:36 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/10/03 17:34:08 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_char(char *str, int *i, char c)
{
	while (str[*i] == c)
		(*i)++;
}

bool	is_position_char(int c)
{
	return ((c == 'N') || (c == 'E') || (c == 'S') || (c == 'W'));
}
