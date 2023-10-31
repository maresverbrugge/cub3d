/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:01:49 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/12/17 11:44:35 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

int	printchar(int c)
{
	return (write(1, &c, 1));
}

int	printnum(int num)
{
	int		len;
	char	*str;

	str = ft_itoa(num);
	if (!str)
		return (-1);
	len = printstring(str);
	free(str);
	return (len);
}

int	printstring(const char *str)
{
	int	len;
	int	bytesprinted;

	if (!str)
		return (printstring("(null)"));
	len = 0;
	while (str[len])
	{
		bytesprinted = write(1, &str[len], 1);
		if (bytesprinted == -1)
			return (bytesprinted);
		len++;
	}
	return (len);
}

int	printpercent(void)
{
	return (write(1, "%", 1));
}
