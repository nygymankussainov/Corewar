/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_ox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:01:17 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:36:15 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						ft_write_ox(t_spec *argument, char *number, int digits,
										int reg)
{
	int i;

	i = 0;
	if (number[0] == '0' && (argument->precision == -1))
	{
		if (argument->width == 0)
			number[0] = '\0';
		if (argument->type == 'x' || argument->type == 'X')
		{
			free(argument->flags);
			argument->flags = NULL;
		}
		number[0] = '\0';
		argument->width++;
		i = 1;
	}
	if (digits >= argument->width && digits >= argument->precision)
		return (ft_write_ox_case1(argument, number, digits, reg) - i);
	else
		return (argument->precision >= argument->width) ?
			(ft_write_ox_case2(argument, number, digits, reg)) :
			(ft_write_ox_case3(argument, number, digits, reg) - i);
}

int						ft_solve_ox(t_spec *argument, va_list arg, int base,
										int reg)
{
	unsigned long long	ox;
	char				*number;
	int					digits;
	int					n;

	if (!ft_valid_flags(argument, 0))
		return (-1);
	if (!argument->size && argument->type != 'O')
		ox = va_arg(arg, unsigned int);
	else if (argument->type == 'O' || (argument->size)[0] == 'l')
		ox = va_arg(arg, unsigned long long);
	else if ((argument->size)[0] == 'h' && !(argument->size)[1])
		ox = (unsigned short)va_arg(arg, int);
	else
		ox = (unsigned char)va_arg(arg, int);
	number = (argument->type == 'o') ? ft_change_system(ox, base)
				: ft_change_system_over_ten(ox, base, reg);
	if (!number)
		return (-1);
	digits = ft_strlen(number);
	n = ft_write_ox(argument, number, digits, reg);
	ft_strdel(&number);
	return (n);
}
