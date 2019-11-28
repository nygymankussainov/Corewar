/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:35:33 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:34:30 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_negative_prec(t_spec *argument, va_list arg, const char **str,
								int i)
{
	if (i == -3)
	{
		argument->precision = va_arg(arg, int);
		if (argument->precision <= 0)
			argument->precision = (argument->precision == 0) ? -1 : 0;
	}
	else
		argument->precision = -1;
	if (i == -1 || i == -3)
		(*str)++;
	return (i == -2) ? -1 : 1;
}

int			ft_find_len(const char **str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if ((*str)[j] == 48)
		(*str)++;
	while ((*str)[j] && (*str)[j] != 37 && !((*str)[j] >= 65 && (*str)[j] <= 90)
		&& !((*str)[j] >= 97 && (*str)[j] <= 122))
	{
		if (((*str)[j] >= 48 && (*str)[j] <= 57))
		{
			i++;
			j++;
		}
		else if ((*str)[j] == '*')
			return (-3);
		else
			return (i);
	}
	return (i);
}

void		ft_write_precision(const char **str, char **precision, int i)
{
	int		n;

	n = 0;
	while (n < i)
	{
		(*precision)[n++] = **str;
		(*str)++;
	}
	(*precision)[n] = '\0';
}

int			ft_get_precision(const char **str, t_spec *argument, va_list arg)
{
	int		i;
	char	*precision;

	if (**str != '.')
	{
		argument->precision = 0;
		return (1);
	}
	while (**str == '.')
		(*str)++;
	i = ft_find_len(str);
	if (i <= 0)
		return (ft_negative_prec(argument, arg, str, i));
	if (!(precision = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	ft_write_precision(str, &precision, i);
	argument->precision = ft_atoi(precision);
	if (argument->precision == 0)
		argument->precision = -1;
	else if (argument->precision < 0)
		argument->precision = 0;
	ft_strdel(&precision);
	return (1);
}
