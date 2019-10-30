/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fract_to_dec_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:08:28 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:34:09 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		*ft_sum(char *sum, char *bas, int c, int zs)
{
	int		tmp1;
	int		tmp2;
	int		tmp3;
	int		carry;
	int		i;

	i = c - 1;
	while ((c-- > zs || (i >= 0 && sum[i] == ':')))
	{
		tmp1 = sum[i] - '0';
		tmp2 = bas[c] - '0';
		carry = (tmp1 + tmp2) / 10;
		if (i - 1 >= 0)
		{
			tmp3 = sum[i - 1] - '0';
			sum[i - 1] = (tmp3 + carry) + '0';
		}
		sum[i--] = (tmp1 + tmp2) % 10 + '0';
	}
	return (sum);
}

char		*ft_multiply(char *base, int c, int zs)
{
	int		temp;
	int		carry;
	int		i;
	int		j;

	i = c - 1;
	carry = 0;
	while (c-- > zs)
	{
		if (i - 1 >= 0)
		{
			j = base[i - 1] - '0';
			base[i - 1] = '0';
		}
		else
			j = 0;
		temp = j * 5;
		base[i--] = carry + temp % 10 + '0';
		carry = temp / 10;
	}
	return (base);
}

char		*ft_get_fraction(char *bin, int len, int zs, int count)
{
	char	*sum;
	char	*base;
	int		i;
	int		end_zs;

	i = 0;
	end_zs = ft_strlen(bin);
	while (end_zs > 0 && bin[end_zs] == '0')
		end_zs--;
	if (!(base = ft_fill_zero(len)) ||
				!(sum = ft_fill_zero(len)))
		return (NULL);
	base[0] = '5';
	if (bin[0] && bin[i++] == '1')
		sum[0] = '5';
	while (bin[0] && bin[i] && ++count && i < end_zs + 1)
	{
		base = ft_multiply(base, count, zs);
		while (base[zs] == '0')
			zs++;
		if (bin[i++] == '1')
			sum = ft_sum(sum, base, count, zs);
	}
	ft_strdel(&base);
	return (sum);
}
