/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_itoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 18:49:51 by screight          #+#    #+#             */
/*   Updated: 2019/12/05 18:58:42 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static int	ft_len(int n, char sign)
{
	int		len;

	len = 1;
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	if (sign == '-')
		len++;
	return (len);
}

void		v_itoa(int n, char *str)
{
	char	sign;
	int		len;

	sign = 0;
	if (n < 0)
	{
		sign = '-';
		n = -n;
	}
	len = ft_len(n, sign);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
	}
	if (sign == '-')
		str[0] = sign;
}
