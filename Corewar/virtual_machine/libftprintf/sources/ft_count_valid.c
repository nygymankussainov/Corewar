/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 21:03:35 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:33:51 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_count_valid_diu(t_spec *argument, char type)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while ((argument->flags)[i])
	{
		if (((type == 'u' || type == 'U') && ((argument->flags)[i] == '+'
			|| (argument->flags)[i] == ' ')) || (argument->flags)[i] == '#')
			(argument->flags)[i] = 'x';
		i++;
	}
	i = 0;
	while ((argument->flags)[i])
	{
		if ((argument->flags)[i++] != 'x')
			count++;
	}
	return (count == i) ? -1 : count;
}

int			ft_count_valid_ox(t_spec *argument)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while ((argument->flags)[i])
	{
		if ((argument->flags)[i] == '+' || (argument->flags)[i] == ' ')
			(argument->flags)[i] = 'x';
		i++;
	}
	i = 0;
	while ((argument->flags)[i])
	{
		if ((argument->flags)[i++] != 'x')
			count++;
	}
	return (count == i) ? -1 : count;
}

int			ft_count_valid_perc(t_spec *argument)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while ((argument->flags)[i])
	{
		if ((argument->flags)[i] == '#' || (argument->flags)[i] == ' '
			|| (argument->flags)[i] == '+')
			(argument->flags)[i] = 'x';
		i++;
	}
	i = 0;
	while ((argument->flags)[i])
	{
		if ((argument->flags)[i++] != 'x')
			count++;
	}
	return (count == i) ? -1 : count;
}

int			ft_count_valid_ef(t_spec *argument, int *ef)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (argument->flags[i])
	{
		if (argument->flags[i] == '#')
		{
			if (argument->precision == 0)
				*ef = -1;
			argument->flags[i] = 'x';
		}
		i++;
	}
	i = 0;
	while (argument->flags[i])
	{
		if (argument->flags[i++] != 'x')
			count++;
	}
	return (count == i) ? -1 : count;
}

int			ft_count_valid(t_spec *argument, char type, int *ef)
{
	if (type == 'd' || type == 'D' || type == 'i' || type == 'u' || type == 'U')
		return (ft_count_valid_diu(argument, type));
	else if (type == 'o' || type == 'O' || type == 'x' || type == 'X')
		return (ft_count_valid_ox(argument));
	else if (type == '%')
		return (ft_count_valid_perc(argument));
	else
		return (ft_count_valid_ef(argument, ef));
}
