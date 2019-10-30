/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_d_case3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 20:53:21 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:35 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_d3_sign(t_spec *argument, char *number)
{
	if (number[0] != '-' && (((argument->flags)[0] == '+')
		|| ((argument->flags)[1] && ((argument->flags)[0] == '+'
			|| (argument->flags)[1] == '+'))))
		(number[0] == '-') ? write(1, "-", 1) : write(1, "+", 1);
	else if (number[0] != '-' && (((argument->flags)[0] == ' ')
		|| ((argument->flags)[1] && ((argument->flags)[0] == ' '
			|| (argument->flags)[1] == ' '))))
		write(1, " ", 1);
}

int			ft_write_d_case3(t_spec *argument, char *number, int digits)
{
	int		i;
	int		zero;

	i = 0;
	zero = argument->precision - digits;
	if ((argument->flags) && (number[0] != '-' && (((argument->flags)[0] == '+'
		|| (argument->flags)[0] == ' ') || (argument->flags)[1])))
		i++;
	if (argument->flags)
		ft_d3_sign(argument, number);
	if (number[0] == '-')
	{
		write(1, "-", 1);
		number++;
		i++;
	}
	while (zero-- > 0)
		write(1, "0", 1);
	while (*number)
		write(1, number++, 1);
	return (argument->precision + i);
}
