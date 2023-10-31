/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mverbrug <mverbrug@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/23 18:45:34 by mverbrug      #+#    #+#                 */
/*   Updated: 2022/10/12 10:57:55 by mverbrug      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
* The isdigit() function tests for a decimal digit character.
* Returns 1 if character is decimal digit.
* Returns 0 if character is not a decimal digit.
*/

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
