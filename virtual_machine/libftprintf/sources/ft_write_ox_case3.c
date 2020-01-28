/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_ox_case3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:48:38 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:59 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_ox_ret(t_spec *arg, char *number, int spaces, int diff)
{
	while (diff-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	while (((arg->flags)[0] == '-' || ((arg->flags)[1] &&
		(arg->flags)[1] == '-')) && spaces-- > 0)
		write(1, " ", 1);
	return (arg->width);
}

int			ft_ox_case3_noflags(t_spec *arg, char *number, int spaces, int dig)
{
	int		difference;

	difference = arg->precision - dig;
	if (difference > 0)
		spaces = spaces - difference;
	while (spaces-- > 0)
		write(1, " ", 1);
	while (difference-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	return (arg->width);
}

int			ft_cont(t_spec *arg, char *number, int dig, int registr)
{
	int		spaces;
	int		difference;

	spaces = arg->width - dig;
	difference = arg->precision - dig;
	spaces = (difference > 0) ? spaces - difference : spaces;
	if (number[0] != '0')
		spaces = (arg->type == 'o' || arg->type == 'O') ? spaces - 1
			: spaces - 2;
	while (arg->flags[0] != '-' && arg->flags[1] != '-' && spaces-- > 0)
		write(1, " ", 1);
	if (number[0] != '0')
	{
		if (arg->type == 'o' || arg->type == 'O')
		{
			if (arg->precision > dig)
				(arg->flags[0] == '-' || arg->flags[1] == '-')
				? ++spaces : write(1, " ", 1);
			else
				write(1, "0", 1);
		}
		else
			(registr == 0) ? write(1, "0x", 2) : write(1, "0X", 2);
	}
	return (ft_ox_ret(arg, number, spaces, difference));
}

int			ft_ox_flags(t_spec *arg, char *number, int dig, int reg)
{
	int		spaces;
	int		diff;

	spaces = arg->width - dig;
	diff = arg->precision - dig;
	spaces = (diff > 0) ? spaces - diff : spaces;
	if ((arg->flags[0] == '0' && !arg->flags[1]) || ((arg->flags[0] == '0'
		|| arg->flags[1] == '0') && arg->precision == 0))
	{
		if (arg->precision == -1 || arg->precision > 0)
		{
			while (spaces-- > 0)
				write(1, " ", 1);
		}
		if (arg->flags[1] && number[0] != '0' && (arg->type == 'x'
			|| arg->type == 'X'))
		{
			(reg == 0) ? write(1, "0x", 2) : write(1, "0X", 2);
			spaces -= 2;
		}
		return (arg->precision == 0) ? (ft_ox_ret(arg, number, 0, spaces))
		: (ft_ox_ret(arg, number, spaces, diff));
	}
	return (arg->flags[0] == '-' && !arg->flags[1]) ?
	(ft_ox_ret(arg, number, spaces, diff)) : (ft_cont(arg, number, dig, reg));
}

int			ft_write_ox_case3(t_spec *arg, char *number, int digits,
								int registr)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = arg->width - digits;
	if ((arg->type == 'x' || arg->type == 'X') && number[0] != '0'
		&& (arg->width - digits == 1 || arg->width - arg->precision == 1)
		&& arg->flags && (arg->flags[0] == '#' || arg->flags[1] == '#'))
		i++;
	if (arg->precision == -1 && number[0] == '0')
	{
		spaces = arg->width;
		while (spaces--)
			write(1, " ", 1);
		return (arg->width);
	}
	if (!(arg->flags))
		return (ft_ox_case3_noflags(arg, number, spaces, digits));
	else
		return (ft_ox_flags(arg, number, digits, registr) + i);
}
