/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:32:31 by screight          #+#    #+#             */
/*   Updated: 2019/02/13 19:32:38 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_minint(int n)
{
	int		len;
	char	*str;

	len = 12;
	n = -(n / 10);
	if (!(str = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	str[--len] = '\0';
	str[--len] = '8';
	while (len)
	{
		len--;
		str[len] = (n % 10) + '0';
		n = n / 10;
	}
	str[len] = '-';
	return (str);
}

static int		ft_len(int n, char sign)
{
	int	len;

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

char			*ft_itoa(int n)
{
	char	sign;
	int		len;
	char	*str;

	sign = 0;
	if (n == -2147483648)
		return (str = ft_minint(n));
	if (n < 0)
	{
		sign = '-';
		n = -n;
	}
	len = ft_len(n, sign);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
	}
	if (sign == '-')
		str[0] = sign;
	return (str);
}
