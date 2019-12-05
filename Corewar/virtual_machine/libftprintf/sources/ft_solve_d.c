/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:13:48 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:35:57 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_write_d(t_spec *argument, char *number, int digits)
{
	int i;

	i = 0;
	if (number[0] == '0' && argument->precision == -1)
	{
		if (argument->width == 0)
		{
			while (argument->flags && (argument->flags)[i])
			{
				if ((argument->flags)[i] == '+' || (argument->flags)[i] == ' ')
					argument->width++;
				i++;
			}
		}
		number[0] = '\0';
		argument->width++;
		i = 1;
	}
	else if (digits >= argument->width && digits >= argument->precision)
		return (ft_write_d_case1(argument, number, digits) - i);
	return ((argument->width > argument->precision) ?
	(ft_write_d_case2(argument, number, digits) - i) :
	(ft_write_d_case3(argument, number, digits)));
}

int				ft_solve_d(t_spec *argument, va_list arg)
{
	long long	d;
	char		*number;
	int			digits;
	int			n;

	if (!(ft_valid_flags(argument, 0)))
		return (-1);
	if (!argument->size && argument->type != 'D')
		d = va_arg(arg, int);
	else if (argument->type == 'D' || (argument->size)[0] == 'l')
		d = va_arg(arg, long long);
	else if ((argument->size)[0] == 'h' && !(argument->size)[1])
		d = (short)va_arg(arg, int);
	else
		d = (char)va_arg(arg, int);
	if (!(number = ft_itoa_long(d)))
		return (-1);
	digits = ft_count_digits(number);
	n = ft_write_d(argument, number, digits);
	ft_strdel(&number);
	return (n);
}
