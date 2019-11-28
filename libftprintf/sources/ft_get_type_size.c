/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:48:12 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:34:38 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_search_other(const char *str, int n)
{
	int			i;

	i = 0;
	if (str[i] == 'h')
	{
		if (str[++i] == 'l')
			return (n);
		else
			return (0);
	}
	return (0);
}

int				ft_check_next_word(const char **str, int i)
{
	int			n;

	if ((*str)[i] == 'L')
	{
		n = i + 1;
		if ((*str)[n] == 'f')
			return (1);
		(*str)++;
		return (0);
	}
	else
	{
		i++;
		if ((*str)[i] == 'l' || (*str)[i] == 'h')
		{
			n = ((*str)[i] == (*str)[i - 1]) ? ft_search_other(((*str) + i), 2)
				: ft_search_other(*str, 1);
			(*str) = (*str) + n;
			return (n == 0) ? 2 : 1;
		}
		else
			return (1);
	}
}

int				ft_is_type_valid(const char **str)
{
	int			i;
	int			j;
	static char	conversions[] = "dDioOuUxXfcCsSp%";

	i = 0;
	j = 0;
	if ((*str)[i] != 'l' && (*str)[i] != 'L' && (*str)[i] != 'h'
		&& (*str)[i] != 'j' && (*str)[i] != 'z')
	{
		while (conversions[j])
		{
			if ((*str)[i] != conversions[j])
				j++;
			else
				return (0);
		}
		return (0);
	}
	else
		return (ft_check_next_word(str, i));
}

int				ft_get_type_size(const char **str, t_spec *argument)
{
	int			i;
	int			n;

	n = 0;
	i = ft_is_type_valid(str);
	if (i == -1)
		return (-1);
	else if (i == 0)
	{
		argument->size = NULL;
		return (1);
	}
	else
	{
		if (!(argument->size = (char *)malloc(sizeof(char) * (i + 1))))
			return (0);
		while (n < i)
		{
			(argument->size)[n++] = (**str == 'j' || **str == 'z')
				? 'l' : **str;
			(*str)++;
		}
		argument->size[i] = '\0';
		return (1);
	}
}
