/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 14:28:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 12:20:22 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_digit_ll(__int128_t n, int len)
{
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa_ll(__int128_t n)
{
	char	*result;
	int		len;
	int		sign;

	sign = n < 0 ? 1 : 0;
	n = sign ? -n : n;
	len = ft_count_digit_ll(n, 1) + sign;
	if (!(result = ft_memalloc(len + 1)))
		return (NULL);
	result[len--] = '\0';
	while (len >= 0)
	{
		result[len--] = (n % 10) + '0';
		n /= 10;
	}
	if (result[0] == '0' && sign)
		result[0] = '-';
	return (result);
}
