/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:06:08 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:36:26 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_solve_percent(t_spec *argument)
{
	int		spaces;
	int		count;

	if (argument->width != 0)
		count = argument->width;
	else
		count = 1;
	if (!(ft_valid_flags(argument, 0)))
		return (-1);
	spaces = argument->width - 1;
	if (argument->flags && (argument->flags)[0] == '-')
		write(1, "%", 1);
	while (spaces-- > 0)
	{
		if (argument->flags && (argument->flags)[0] == '0')
			write(1, "0", 1);
		else
			write(1, " ", 1);
	}
	if (!(argument->flags) || ((argument->flags) &&
		(argument->flags)[0] != '-'))
		write(1, "%", 1);
	return (count);
}
