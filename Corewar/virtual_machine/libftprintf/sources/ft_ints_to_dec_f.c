/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ints_to_dec_f.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:11:54 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:35:37 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_int_str_rev(char *str)
{
	int		i;
	int		len;
	char	*rev_str;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	rev_str = (char *)malloc(sizeof(char) * (len + 1 + 1));
	while (len--)
		rev_str[i++] = str[len];
	rev_str[i++] = '.';
	rev_str[i] = '\0';
	ft_strdel(&str);
	return (rev_str);
}

int			ft_sum_int(char **sum, char *base, int sign1, int sign)
{
	int		tmp1;
	int		tmp2;
	int		tmp3;
	int		i;

	i = 0;
	++sign;
	while (i < sign1)
	{
		tmp1 = (*sum)[i] - '0';
		tmp2 = base[i] - '0';
		tmp3 = (*sum)[i + 1] - '0';
		(*sum)[i + 1] = (tmp3 + (tmp1 + tmp2) / 10) + '0';
		(*sum)[i++] = (tmp1 + tmp2) % 10 + '0';
	}
	return (sign1);
}

int			ft_multiply_ints(char **base, int significant)
{
	int		temp;
	int		carry;
	int		i;
	int		j;

	i = 0;
	carry = 0;
	++significant;
	while (i < significant)
	{
		j = (*base)[i] - '0';
		temp = j * 2;
		(*base)[i++] = carry + temp % 10 + '0';
		carry = temp / 10;
	}
	return (significant);
}

char		*ft_get_ints(char *bin, int ints, int len, int sign1)
{
	char	*sum;
	char	*base;
	int		sign;

	sign = 0;
	len = (len == 53) ? 308 : 4932;
	if (!(base = ft_fill_zero(len + 2)) ||
				!(sum = ft_fill_zero(len + 2)))
		return (NULL);
	base[0] = '1';
	sum[0] = (bin[ints--] == '1') ? '1' : '0';
	while (ints + 1)
	{
		sign1 = ft_multiply_ints(&base, sign1);
		if (bin[ints--] == '1')
		{
			sign = ft_sum_int(&sum, base, sign1, sign);
			sign = (sum[sign - 1] == '0') ? sign - 1 : sign;
		}
		sign1 = (base[sign1 - 1] == '0') ? sign1 - 1 : sign1;
	}
	sum[sign + 2] = '\0';
	ft_strdel(&base);
	return (sum);
}
