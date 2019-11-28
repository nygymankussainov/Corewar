/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_binary_f.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:56:10 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:35:00 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*ft_complete_str(char *str, int zlen)
{
	char	*zstr;
	char	*rez;

	if (!(zstr = ft_fill_zero(zlen)) ||
					!(rez = ft_strjoin(str, zstr)))
		return (NULL);
	ft_strdel(&zstr);
	return (rez);
}

char		*ft_case_one(char *mantis, int pow, int len, int prec)
{
	char	*str1;
	char	*str2;
	char	*str3;
	int		tlen;

	if (!(str1 = ft_fill_zero(-pow - 1)) ||
			!(str3 = ft_strjoin(str1, mantis)) ||
				(!(str2 = ft_get_fraction(str3, len + (-pow), 0, 1))))
		return (NULL);
	ft_strdel(&str1);
	ft_strdel(&str3);
	if (prec > (tlen = ft_strlen(str2)))
	{
		if ((!(str1 = ft_fill_zero(prec - tlen + 1))) ||
			!(str3 = ft_sjoin_and_free(str2, str1)))
			return (NULL);
	}
	if (!str3)
		str3 = str2;
	str1 = ft_strjoin("000.", str3);
	ft_strdel(&str3);
	return (str1);
}

char		*ft_assign_str(char *mantis, int pow, int len)
{
	char	*str;

	str = NULL;
	if (pow > len)
	{
		if (!(str = ft_complete_str(mantis, pow - len)))
			return (NULL);
	}
	if (!str)
		str = mantis;
	return (str);
}

char		*ft_mantis_to_decimal(char *mantis, int pow, int len, int prec)
{
	char	*str;
	char	*int_part;
	char	*frac_part;
	int		tlen;

	if (pow < 0)
		return (ft_case_one(mantis, pow, len, prec));
	else
	{
		str = ft_assign_str(mantis, pow, len);
		int_part = ft_int_str_rev(ft_get_ints(str, pow, len, 0));
		len = (len - pow < 0) ? 10 : len - pow;
		tlen = ((int)ft_strlen(str) > pow + 1) ? pow + 1 : (int)ft_strlen(str);
		frac_part = ft_get_fraction(str + tlen, len, 0, 1);
		if (str != mantis)
			ft_strdel(&str);
		if (prec > len)
		{
			str = frac_part;
			if (!(frac_part = ft_complete_str(str, prec + 1 - len)))
				return (NULL);
			ft_strdel(&str);
		}
		return (ft_sjoin_and_free(int_part, frac_part));
	}
}

int			ft_exponent_to_decimal(char *num)
{
	int		len;
	int		decimal;
	int		base;

	decimal = 0;
	len = 0;
	base = 1;
	while (num[len])
		len++;
	while (len--)
	{
		decimal = decimal + (num[len] - '0') * base;
		base *= 2;
	}
	return (decimal);
}
