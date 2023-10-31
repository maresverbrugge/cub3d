/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 12:28:09 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/12/17 11:44:06 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int	conversions(const char *str, va_list ap)
{
	if (*str == 'c')
		return (printchar(va_arg(ap, int)));
	if (*str == 's')
		return (printstring(va_arg(ap, char *)));
	if (*str == 'p')
		return (printptr(va_arg(ap, unsigned long long)));
	if (*str == 'd' || *str == 'i')
		return (printnum(va_arg(ap, int)));
	if (*str == 'u')
		return (printunsignedint(va_arg(ap, unsigned int)));
	if (*str == 'x' || *str == 'X')
		return (printhex(va_arg(ap, unsigned int), *str));
	if (*str == '%')
		return (printpercent());
	else
		return (printchar(*str));
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		bytesprinted;
	int		checkerror;

	bytesprinted = 0;
	va_start(ap, str);
	while (*str)
	{
		checkerror = 0;
		if (*str == '%' && *(str + 1) != '\0')
		{
			str++;
			checkerror = conversions(str, ap);
		}
		else if (*str != '%')
			checkerror = write(1, str, 1);
		if (checkerror == -1)
			return (-1);
		bytesprinted += checkerror;
		str++;
	}
	va_end(ap);
	return (bytesprinted);
}
/*
#include <stdio.h>
int	main(void)
{
	ft_printf("%d", -10);
	printf("%d", -10);
	return (0);
}
*/
