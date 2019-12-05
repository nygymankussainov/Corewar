/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 17:07:12 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:07 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						ft_write_u(t_spec *argument, char *number, int digits)
{
	int i;

	i = 0;
	if (number[0] == '0' && (argument->precision == -1))
	{
		free(argument->flags);
		argument->flags = NULL;
		number[0] = '\0';
		argument->width++;
		i = 1;
	}
	if (argument->width >= argument->precision && argument->width >= digits)
		return (ft_write_u_case2(argument, number, digits) - i);
	return (ft_write_u_case1(argument, number, digits));
}

int						ft_solve_u(t_spec *argument, va_list arg)
{
	unsigned long long	u;
	char				*number;
	int					digits;
	int					n;

	if (!(ft_valid_flags(argument, 0)))
		return (-1);
	if (!argument->size && argument->type != 'U')
		u = va_arg(arg, unsigned int);
	else if (argument->type == 'U' || (argument->size)[0] == 'l')
		u = va_arg(arg, unsigned long long);
	else if ((argument->size)[0] == 'h' && !(argument->size)[1])
		u = (unsigned short)va_arg(arg, int);
	else
		u = (unsigned char)va_arg(arg, int);
	if (!(number = ft_itoa_un_long(u)))
		return (0);
	digits = ft_strlen(number);
	n = ft_write_u(argument, number, digits);
	ft_strdel(&number);
	return (n);
}
