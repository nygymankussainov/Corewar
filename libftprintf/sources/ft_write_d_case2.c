/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_d_case2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:47:56 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:29 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_d2_noflag(t_spec *argument, char *number, int spaces, int difference)
{
	if (number[0] == '-')
		spaces--;
	while (spaces-- > 0)
		write(1, " ", 1);
	if (number[0] == '-')
	{
		write(1, "-", 1);
		number++;
	}
	while (difference-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	return (argument->width);
}

int		ft_d2_zero_minus(t_spec *argument, char *number, int spaces, int diff)
{
	if (number[0] == '-')
	{
		spaces--;
		if (argument->flags[0] == '-')
		{
			write(1, "-", 1);
			number++;
		}
	}
	if (argument->flags[0] == '0')
	{
		if (argument->precision == 0 && number[0] == '-')
			write(1, number++, 1);
		while (spaces-- > 0)
			argument->precision == 0 ? write(1, "0", 1) : write(1, " ", 1);
		if (argument->precision != 0 && number[0] == '-')
			write(1, number++, 1);
	}
	while (diff-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	while (spaces-- > 0 && argument->flags[0] == '-')
		write(1, " ", 1);
	return (argument->width);
}

int		ft_d2_plus_space(t_spec *argument, char *number, int spaces, int diff)
{
	spaces--;
	while (spaces-- > 0)
		write(1, " ", 1);
	if ((argument->flags)[0] == '+')
	{
		(number[0] == '-') ? write(1, "-", 1) : write(1, "+", 1);
		if (number[0] == '-')
			number++;
	}
	else
	{
		number[0] == '-' ? write(1, "-", 1) : write(1, " ", 1);
		if (number[0] == '-')
			number++;
	}
	while (diff-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	return (argument->width);
}

int		ft_d2_twoflags(t_spec *argument, char *number, int spaces, int diff)
{
	spaces--;
	if ((argument->flags)[0] == '0' || (argument->flags)[1] == '0')
	{
		while (argument->precision != 0 && spaces-- > 0)
			write(1, " ", 1);
	}
	if ((argument->flags)[0] == '+' || (argument->flags)[1] == '+')
		(number[0] == '-') ? write(1, "-", 1) : write(1, "+", 1);
	else
		(number[0] != '-') ? write(1, " ", 1) : write(1, "-", 1);
	if (number[0] == '-')
		number++;
	while (diff-- > 0 || (((argument->flags)[0] == '0' ||
		(argument->flags)[1] == '0') && argument->precision == 0
			&& spaces-- > 0))
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	while (((argument->flags)[0] == '-' || (argument->flags)[1] == '-')
		&& spaces-- > 0)
		write(1, " ", 1);
	return (argument->width);
}

int		ft_write_d_case2(t_spec *argument, char *number, int digits)
{
	int		i;
	int		spaces;
	int		difference;

	i = 0;
	spaces = argument->width - digits;
	difference = argument->precision - digits;
	if (argument->width == argument->precision && (argument->flags))
	{
		if (((argument->flags)[0] == '+' || (argument->flags)[0] == ' ')
			|| (argument->flags)[1])
			i++;
	}
	if (difference > 0)
		spaces = spaces - difference;
	if (!(argument->flags))
		return (ft_d2_noflag(argument, number, spaces, difference) + i);
	else if (!((argument->flags)[1]))
		return ((argument->flags)[0] == '+' || (argument->flags)[0] == ' ') ?
		(ft_d2_plus_space(argument, number, spaces, difference) + i) :
		(ft_d2_zero_minus(argument, number, spaces, difference) + i);
	else
		return (ft_d2_twoflags(argument, number, spaces, difference) + i);
}
