/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printunsignedint.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:21:47 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/11/02 17:27:51 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

static int	unsignedintlen(unsigned int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		num = num / 10;
		len ++;
	}
	return (len);
}

int	printunsignedint(unsigned int num)
{
	int		len;
	char	*str;

	if (num == 0)
		return (write(1, "0", 1));
	len = unsignedintlen(num);
	str = malloc(len + 1);
	if (!str)
		return (-1);
	str[len--] = '\0';
	while (num != 0)
	{
		str[len--] = num % 10 + '0';
		num = num / 10;
	}
	len = printstring(str);
	free(str);
	return (len);
}
