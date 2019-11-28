/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 16:10:43 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:33:58 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_edit_flags(t_spec *argument, char ch)
{
	int		n;
	int		i;
	char	*result;
	char	*swap;

	n = 1;
	i = 0;
	while (argument->flags && (argument->flags)[i])
	{
		if ((argument->flags)[i] == ch)
			return (1);
		i++;
	}
	result = (char *)malloc(sizeof(char) * (n + i + 1));
	n = 0;
	result[n++] = ch;
	while (--i >= 0)
		result[n++] = (argument->flags)[i];
	result[n] = '\0';
	swap = argument->flags;
	argument->flags = result;
	ft_strdel(&swap);
	argument->precision = 0;
	return (1);
}
