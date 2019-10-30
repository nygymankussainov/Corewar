/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 21:45:43 by screight          #+#    #+#             */
/*   Updated: 2018/12/19 21:52:20 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
				str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (res < 0)
			return (sign < 0 ? 0 : -1);
	}
	res = res * sign;
	return (res);
}
