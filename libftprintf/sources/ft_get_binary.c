/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 21:18:16 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:34:17 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_get_exponent(unsigned long binary, char **num, int start)
{
	int		bin;
	int		j;
	int		end;

	end = 52;
	j = 0;
	while (start-- > end)
	{
		bin = (binary >> start) & 1u;
		(*num)[j++] = bin + '0';
	}
	(*num)[j] = '\0';
}

void		ft_get_binary(unsigned long binary, char **num, int start, int exp)
{
	int		bin;
	int		j;

	j = 0;
	if (exp != 33000)
	{
		if (exp == 0)
			(*num)[j++] = '0';
		else
			(*num)[j++] = '1';
	}
	while (start-- > 0)
	{
		bin = (binary >> start) & 1u;
		(*num)[j++] = bin + '0';
	}
	(*num)[j] = '\0';
}
