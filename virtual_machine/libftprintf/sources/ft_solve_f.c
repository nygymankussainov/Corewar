/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 16:10:31 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:36:03 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_handle_precision(t_spec *argument)
{
	int		prec;

	prec = argument->precision;
	if (argument->precision == 0)
		prec = 6;
	else if (argument->precision == -1)
		prec = 0;
	return (prec);
}

int			ft_solve_f(t_spec *argument, va_list arg)
{
	char	*snum;
	int		ret;

	snum = NULL;
	argument->precision = ft_handle_precision(argument);
	if (argument->size && argument->size[0] == 'L')
		ret = ft_handle_long_double(&snum, argument, arg);
	else
		ret = ft_handle_double(&snum, argument, arg);
	return (ret);
}
