/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_d_case1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:36:52 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:24 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_write_d_case1(t_spec *argument, char *number, int digits)
{
	digits++;
	if (argument->flags)
	{
		if ((!(argument->flags)[1] && ((argument->flags)[0] == '-' ||
			(argument->flags)[0] == '0')) && (number[0] != '-'))
			digits--;
		else
		{
			if ((argument->flags)[0] == '+' || ((argument->flags)[1] &&
				(argument->flags)[1] == '+'))
			{
				(number[0] == '-') ? write(1, "-", 1) : write(1, "+", 1);
				if (number[0] == '-')
					number++;
			}
			else if (number[0] != '-')
				write(1, " ", 1);
		}
	}
	else if (number[0] != '-')
		digits--;
	while (*number)
		write(1, number++, 1);
	return (digits);
}
