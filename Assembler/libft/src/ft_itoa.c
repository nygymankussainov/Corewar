/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 23:17:59 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/30 23:18:32 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_digit(int n, int len)
{
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = ft_count_digit(n, 1);
	if (!(result = ft_memalloc(len + 1)))
		return (NULL);
	result[len--] = '\0';
	while (len >= 0)
	{
		result[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
