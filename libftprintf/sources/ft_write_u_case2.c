/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_u_case2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:57:26 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:38:16 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_u_case2_flag(t_spec *argument, char *number, int spaces,
								int difference)
{
	while ((argument->flags)[0] != '-' && spaces-- > 0)
		((argument->flags)[0] == '0' && (argument->precision >= argument->width
			|| argument->precision == 0))
			? write(1, "0", 1) : write(1, " ", 1);
	while (difference-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	while (spaces-- > 0 && (argument->flags)[0] == '-')
		write(1, " ", 1);
	return (argument->width);
}

int			ft_write_u_case2(t_spec *argument, char *number, int digits)
{
	int		spaces;
	int		difference;

	spaces = argument->width - digits;
	difference = argument->precision - digits;
	if (difference > 0)
		spaces = spaces - difference;
	if (!(argument->flags))
	{
		while (spaces-- > 0)
			write(1, " ", 1);
		while (difference-- > 0)
			write(1, "0", 1);
		while (*number)
			write(1, number++, 1);
		return (argument->width);
	}
	else
		return (ft_u_case2_flag(argument, number, spaces, difference));
}
