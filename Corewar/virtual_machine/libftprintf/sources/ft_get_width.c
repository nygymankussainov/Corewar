/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:53:34 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:34:54 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_negative_width(t_spec *argument, va_list arg, const char **str,
								int i)
{
	if (i == -3)
	{
		argument->width = va_arg(arg, int);
		if (argument->width < 0)
		{
			ft_edit_flags(argument, '-');
			argument->width = argument->width * -1;
		}
		(*str)++;
	}
	else
		(argument->width) = 0;
	return (i == -1) ? -1 : 1;
}

int			ft_find_width(const char **str, va_list arg, int i, int n)
{
	while ((*str)[i] && (!((*str)[i] == '.' || ((*str)[i] >= 65 &&
		(*str)[i] <= 90) || ((*str)[i] >= 97 && (*str)[i] <= 122)
			|| (*str)[i] == '%')))
	{
		if ((*str)[i] >= 48 && (*str)[i] <= 57)
		{
			n++;
			i++;
		}
		else if ((*str)[i] == '*')
		{
			if ((*str)[i + 1] >= 48 && (*str)[i + 1] <= 57)
			{
				(*str)++;
				va_arg(arg, int);
			}
			else
				return (-3);
		}
		else
			i++;
	}
	return (n);
}

int			ft_get_width(const char **str, t_spec *argument, va_list arg)
{
	char	*width;
	int		i;
	int		n;

	i = ft_find_width(str, arg, 0, 0);
	if (i <= 0)
		return (ft_negative_width(argument, arg, str, i));
	if (!(width = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	n = 0;
	while (n < i)
	{
		width[n++] = **str;
		(*str)++;
	}
	width[n] = '\0';
	argument->width = ft_atoi(width);
	if (argument->width < 0)
		argument->width = 0;
	ft_strdel(&width);
	return (1);
}
