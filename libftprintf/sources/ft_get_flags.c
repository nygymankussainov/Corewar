/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:22:41 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:34:24 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_is_flags_correct(const char *str)
{
	int			i;
	static char	array[5] = {'-', '+', ' ', '#', '0'};

	while (*str && !(*str == '.' || *str == '*' || (*str >= 49 && *str <= 57) ||
	*str == '%' || (*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122)))
	{
		i = 0;
		while (i < 5)
		{
			if (*str != array[i])
				i++;
			else
				break ;
		}
		if (i != 5)
			str++;
		else
			return (-1);
	}
	if (!*str)
		return (-1);
	return (1);
}

int				ft_count_flags(const char *str, char **temp)
{
	int			n;

	n = 0;
	while (!(*str == '.' || *str == '*' || (*str >= 49 && *str <= 57) ||
	*str == '%' || (*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122)))
	{
		n++;
		str++;
	}
	if (!(*temp = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	return (n);
}

int				ft_del_repeats(char **str, int i, int j)
{
	char		ch;

	while ((*str)[++i])
	{
		while ((*str)[i] && (*str)[i] == 'x')
			i++;
		ch = (*str)[i];
		if ((*str)[i] != '\0')
			j = i + 1;
		if (!(*str)[j])
			break ;
		while ((*str)[j])
		{
			if (ch == (*str)[j++])
				(*str)[j - 1] = 'x';
		}
	}
	i = -1;
	j = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] != 'x')
			j++;
	}
	return (j);
}

int				ft_write_flags(t_spec *argument, char *temp, int n)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(argument->flags = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	while (j < n)
	{
		if (temp[i] != 'x')
			(argument->flags)[j++] = temp[i];
		i++;
	}
	(argument->flags)[j] = '\0';
	return (1);
}

int				ft_get_flags(const char **str, t_spec *argument)
{
	int			n;
	int			i;
	char		*temp;

	argument->flags = NULL;
	if (**str == '.' || (**str >= 49 && **str <= 57) || **str == '%' ||
		**str == '*' || (**str >= 65 && **str <= 90) || (**str >= 97
			&& **str <= 122))
		return (1);
	i = 0;
	if ((n = ft_is_flags_correct(*str)) <= 0)
		return (n == 0) ? 0 : -1;
	if (!(n = ft_count_flags(*str, &temp)))
		return (0);
	while (i < n)
		temp[i++] = *(*str)++;
	temp[i] = '\0';
	n = ft_del_repeats(&temp, -1, 0);
	if (!(ft_write_flags(argument, temp, n)))
		return (0);
	ft_strdel(&temp);
	return (1);
}
