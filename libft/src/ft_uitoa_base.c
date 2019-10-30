/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 18:14:57 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/06/14 18:19:14 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		udigit_count(unsigned long long nb, int base)
{
	int i;

	i = 0;
	while (nb /= base)
		i++;
	return (i + 1);
}

char			*ft_uitoa_base(unsigned long long nb, int base, char c)
{
	char	*str_base;
	char	*result;
	int		i;

	if (c == 'X')
		str_base = "0123456789ABCDEF";
	else
		str_base = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (0);
	i = udigit_count(nb, base);
	result = (char *)ft_memalloc(sizeof(char) * i + 1);
	result[i] = '\0';
	while (i > 0)
	{
		result[i - 1] = str_base[nb % base];
		nb /= base;
		i--;
	}
	return (result);
}
