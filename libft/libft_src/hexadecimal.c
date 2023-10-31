/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hexadecimal.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 16:04:05 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/12/17 11:44:20 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>

static void	puthex(unsigned long num, const char x, char *str)
{
	str--;
	if (num >= 16)
	{
		puthex(num / 16, x, str);
		num = num % 16;
	}
	if (num <= 9)
	{
		*str = num + '0';
	}
	else
	{
		if (x == 'x')
		{
			*str = num + 'a' - 10;
		}
		if (x == 'X')
		{
			*str = num + 'A' - 10;
		}
	}
}

static int	hexlen(unsigned long num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		num = num / 16;
		len ++;
	}
	return (len);
}

int	printhex(unsigned long num, const char x)
{
	int		len;
	char	*str;

	if (num == 0)
		return (write(1, "0", 1));
	len = hexlen(num);
	str = malloc(len + 1);
	if (!str)
		return (-1);
	puthex(num, x, (str + len));
	str[len] = '\0';
	len = printstring(str);
	free(str);
	return (len);
}

int	printptr(unsigned long ptr)
{
	int		len;
	char	*str;

	if (ptr == 0)
		return (printstring("0x0"));
	len = hexlen(ptr) + 2;
	str = malloc(len + 1);
	if (!str)
		return (-1);
	puthex(ptr, 'x', (str + len));
	str[0] = '0';
	str[1] = 'x';
	str[len] = '\0';
	len = printstring(str);
	free(str);
	return (len);
}
