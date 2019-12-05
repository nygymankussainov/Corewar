/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_un_long.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:59:32 by egiant            #+#    #+#             */
/*   Updated: 2019/07/31 17:02:43 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_unlong_len(unsigned long n)
{
	int		len;

	len = 0;
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len + 1);
}

char		*ft_itoa_un_long(unsigned long n)
{
	int		len;
	char	*str;

	len = ft_unlong_len(n);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while ((n / 10) > 0)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
	str[--len] = n + '0';
	return (str);
}
