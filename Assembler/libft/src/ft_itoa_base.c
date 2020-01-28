/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:01:49 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 18:18:06 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_digit_count(long long nb, int base)
{
	int i;

	i = 0;
	while (nb /= base)
		i++;
	return (i + 1);
}

int				ft_get_result(char **result, long long nb, int base)
{
	int		i;

	i = 0;
	if (base == 8 || base == 10)
	{
		i = ft_digit_count(nb, base);
		*result = (char *)ft_memalloc(sizeof(char) * i + 1);
	}
	return (i);
}

char			*ft_itoa_base(long long nb, int base, int j)
{
	char	*str_base;
	char	*result;
	int		i;

	str_base = "0123456789abcdef";
	if (base == 16)
	{
		i = ft_digit_count(nb, base) + j;
		result = (char *)ft_memalloc(sizeof(char) * (i + 1));
		result[0] = j ? '0' : result[0];
		result[1] = j ? 'x' : result[0];
	}
	else
		i = ft_get_result(&result, nb, base);
	result[i] = '\0';
	while (i - j > 0)
	{
		result[i - 1] = str_base[nb % base];
		nb /= base;
		i--;
	}
	return (result);
}
