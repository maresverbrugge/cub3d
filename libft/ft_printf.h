/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 12:30:21 by fhuisman      #+#    #+#                 */
/*   Updated: 2022/12/17 11:41:28 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	printchar(int c);
int	printnum(int num);
int	printstring(const char *str);
int	printpercent(void);
int	printhex(unsigned long num, const char x);
int	printptr(unsigned long ptr);
int	printunsignedint(unsigned int num);

#endif