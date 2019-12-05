/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_special_f.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:52:14 by screight          #+#    #+#             */
/*   Updated: 2019/08/28 19:57:48 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_check_str(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '0')
	{
		if (str[++i] == '\0')
			return (0);
	}
	return (-1);
}

int			ft_int_to_out(t_spec *argument, int sign)
{
	int		n;
	char	*str;

	if (sign == -1)
	{
		str = ft_strdup("-inf.");
		n = ft_write_f(argument, str, 4, 0);
	}
	else
	{
		str = ft_strdup("inf.");
		n = ft_write_f(argument, str, 4, 0);
	}
	ft_strdel(&str);
	return (n);
}

int			ft_handle_inf(t_spec *argument, int sign)
{
	int		i;
	int		trig;

	i = 0;
	trig = 0;
	while (argument->flags && argument->flags[i])
	{
		if (argument->flags[i] == '0' || argument->flags[i] == '#')
		{
			trig = 1;
			while (trig == 1 && argument->flags[i++])
				argument->flags[i - 1] = argument->flags[i];
			i = 0;
		}
		else
			i++;
	}
	if (argument->flags && !argument->flags[0])
		ft_strdel(&argument->flags);
	argument->precision = 0;
	if (!(ft_valid_flags(argument, 0)))
		return (-1);
	return (ft_int_to_out(argument, sign));
}

int			ft_handle_nan(t_spec *argument, int i)
{
	int		trig;
	char	*str;

	trig = 0;
	while (argument->flags && argument->flags[i])
	{
		if (argument->flags[i] == '0' || argument->flags[i] == '#' ||
				argument->flags[i] == '+' || argument->flags[i] == ' ')
		{
			trig = 1;
			while (trig == 1 && argument->flags[i++])
				argument->flags[i - 1] = argument->flags[i];
			i = 0;
		}
		else
			i++;
	}
	if (argument->flags && !argument->flags[0])
		ft_strdel(&argument->flags);
	argument->precision = 0;
	str = ft_strdup("nan.");
	i = ft_write_f(argument, str, 4, 0);
	ft_strdel(&str);
	return (i);
}

int			ft_handle_zero(char *exp, char *mant, t_spec *argument, int sign)
{
	int		e;
	int		m;
	char	*zstr;
	int		i;

	e = ft_check_str(exp);
	m = ft_check_str(mant);
	if (e == 0 && m == 0)
	{
		i = 0;
		zstr = (char *)malloc(sizeof(char) * argument->precision + 6);
		zstr[argument->precision + 5] = '\0';
		while (i < argument->precision + 5)
			zstr[i++] = '0';
		zstr[3] = '.';
		return (ft_output_f(zstr, argument, sign, 0));
	}
	return (-1);
}
