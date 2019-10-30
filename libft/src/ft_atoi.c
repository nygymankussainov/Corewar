/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:58:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/05 15:00:12 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	size_t					i;
	unsigned long long int	result;
	int						sign;

	i = 0;
	result = 0;
	sign = 1;
	i = ft_skip_whitesp(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		if (result > 922337203685477580 && sign == -1 && str[i] > 8)
			return (0);
		else if (result > 922337203685477580 && sign == 1 && str[i] > 7)
			return (-1);
		i++;
	}
	return ((int)(result * sign));
}
