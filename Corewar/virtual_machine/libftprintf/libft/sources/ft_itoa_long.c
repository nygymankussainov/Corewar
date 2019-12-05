/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:58:40 by egiant            #+#    #+#             */
/*   Updated: 2019/07/31 17:02:38 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_longlen(long long n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		if (n == LLONG_MIN)
			return (20);
		n = n * (-1);
		len++;
	}
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len + 1);
}

char		*ft_itoa_long(long long n)
{
	int		len;
	char	*str;

	len = ft_longlen(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == LLONG_MIN)
		{
			str[--len] = '8';
			n = 922337203685477580;
		}
		else
			n = n * (-1);
	}
	while ((n / 10) > 0)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
	str[--len] = n + '0';
	return (str);
}
