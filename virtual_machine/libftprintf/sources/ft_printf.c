/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 18:08:46 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:35:46 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void			ft_free_all(t_spec **argument, t_valid **check)
{
	if ((*argument)->flags)
		free((*argument)->flags);
	if ((*argument)->size)
		free((*argument)->size);
	free(*check);
	free(*argument);
}

int				ft_general(t_spec *argument, va_list arg)
{
	if (argument->type == 'd' || argument->type == 'D'
			|| argument->type == 'i')
		return (ft_solve_d(argument, arg));
	else if (argument->type == 'u' || argument->type == 'U')
		return (ft_solve_u(argument, arg));
	else if (argument->type == 'c' || argument->type == 'C')
		return (ft_solve_c(argument, arg));
	else if (argument->type == 's' || argument->type == 'S')
		return (ft_solve_s(argument, arg));
	else if (argument->type == 'o' || argument->type == 'O')
		return (ft_solve_ox(argument, arg, 8, 1));
	else if (argument->type == 'x')
		return (ft_solve_ox(argument, arg, 16, 0));
	else if (argument->type == 'X')
		return (ft_solve_ox(argument, arg, 16, 1));
	else if (argument->type == '%')
		return (ft_solve_percent(argument));
	else if (argument->type == 'f')
		return (ft_solve_f(argument, arg));
	else
		return (ft_solve_p(argument, arg));
}

int				ft_getinfo(const char **str, va_list arg)
{
	int			count;
	t_spec		*argument;
	t_valid		*check;

	(*str)++;
	if (!(**str))
		return (0);
	if (!(argument = (t_spec *)malloc(sizeof(t_spec)))
		|| !(check = (t_valid *)malloc(sizeof(t_valid))))
		return (-1);
	if (!(check->flags = ft_get_flags(str, argument))
		|| !(check->width = ft_get_width(str, argument, arg)) ||
			!(check->precision = ft_get_precision(str, argument, arg)) ||
				!(check->size = ft_get_type_size(str, argument)) ||
					!(check->type = ft_get_type(str, argument)))
		return (-1);
	if (check->flags == -1 || check->width == -1 || check->precision == -1 ||
			check->size == -1 || check->type == -1)
	{
		ft_free_all(&argument, &check);
		return (0);
	}
	count = ft_general(argument, arg);
	ft_free_all(&argument, &check);
	return (count == -1) ? -1 : count;
}

int				ft_printf(const char *format, ...)
{
	int			i;
	int			result;
	va_list		arg;

	va_start(arg, format);
	result = 0;
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			result++;
			format++;
		}
		else
		{
			i = ft_getinfo(&format, arg);
			if (i == -1)
				return (-1);
			else
				result += i;
		}
	}
	va_end(arg);
	return (result);
}
