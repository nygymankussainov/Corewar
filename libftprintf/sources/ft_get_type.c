/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:52:39 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:34:45 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_valid_type(const char **str, t_spec *arg, char *val, int i)
{
	if (**str == val[i] || (**str == ' ' && *(*str + 1) == '\0'))
	{
		arg->type = (**str == val[i]) ? **str : '0';
		(*str)++;
		return (1);
	}
	else if (**str == '+' || **str == '#' || **str == '-' || **str == '0'
			|| **str == ' ')
	{
		ft_edit_flags(arg, **str);
		(*str)++;
		return (0);
	}
	return (-1);
}

int				ft_get_type(const char **str, t_spec *argument)
{
	static char	valid[] = "dDioOuUxXfcCsSp%";
	int			i;
	int			n;

	while (**str)
	{
		i = 0;
		while (valid[i])
		{
			if ((n = ft_valid_type(str, argument, valid, i)) >= 0)
			{
				if (n == 1)
					return (1);
			}
			else
				i++;
		}
		if (**str == ' ' || **str == '+' || **str == '-' || **str == '0'
			|| **str == '#' || **str == '.' || **str == 'j' || **str == 'z'
				|| **str == 'l' || **str == 'h')
			(*str)++;
		else
			return (-1);
	}
	return (-1);
}
