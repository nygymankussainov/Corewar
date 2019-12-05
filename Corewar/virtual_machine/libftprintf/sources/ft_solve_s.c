/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 18:14:57 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:37:01 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_write_s(t_spec *ar, char *str, int valid, int len)
{
	int		count;
	int		spaces;
	int		i;

	i = 0;
	count = 0;
	if (ar->precision > 0 && ar->precision < len)
		len = ar->precision;
	spaces = ar->width - len;
	if (ar->precision == -1)
	{
		count = ar->width;
		while ((ar->width)-- > 0)
			write(1, " ", 1);
		return (count);
	}
	while (valid == -1 && str[i] && len-- > 0 && ++count)
		ft_putchar(str[i++]);
	while (spaces-- > 0 && ++count)
		valid == 2 ? write(1, "0", 1) : write(1, " ", 1);
	while (valid != -1 && str[i] && len-- > 0 && ++count)
		ft_putchar(str[i++]);
	return (count);
}

int			ft_check_bigs(t_spec *ar, wchar_t *s, int *result)
{
	int		i;
	int		n;
	int		len;

	i = 0;
	n = 0;
	*result = 0;
	while (s[i])
	{
		if (((long)s[i] >= 55296 && (long)s[i] <= 57343) ||
			(long)s[i] >= 1114111 || (long)s[i] < 0)
			return (-1);
		ar->width = 10;
		len = ft_bit_count(s[i++]);
		len = 10 - ft_bigc_width(ar, len);
		if (ar->precision == 0 || (*result + len <= ar->precision))
			*result += len;
		else
			break ;
		n++;
	}
	return (n);
}

int			ft_write_big_s(t_spec *ar, wchar_t *s, int valid, int spaces)
{
	int		i;
	int		n;
	int		count;
	int		num;

	i = 0;
	count = 0;
	if (ar->precision == -1)
	{
		while ((ar->width)-- > 0)
			write(1, " ", 1);
		return (spaces);
	}
	n = ft_check_bigs(ar, s, &num);
	if (n == -1)
		return (-1);
	spaces -= num;
	while (valid != -1 && spaces-- > 0 && ++count)
		(valid != 2) ? write(1, " ", 1) : write(1, "0", 1);
	ar->width = 0;
	while (s[i] && n--)
		count += ft_write_utf(ar, s[i++], 0);
	while (valid == -1 && spaces-- > 0 && ++count)
		write(1, " ", 1);
	return (count);
}

int			ft_solve_s(t_spec *ar, va_list arg)
{
	wchar_t	*s;
	int		valid;
	int		count;
	int		len;

	count = 0;
	if (!(valid = ft_valid_flags_c_s_p(ar)))
		return (0);
	if (!(s = va_arg(arg, void *)))
	{
		count = ft_write_s(ar, "(null)", valid, 6);
		return (count);
	}
	len = (ar->type == 'S' || (ar->size && ar->size[0] == 'l')) ?
	ft_wchar_len(s) : ft_strlen((char *)s);
	count = (ar->type == 'S' || (ar->size && ar->size[0] == 'l')) ?
	ft_write_big_s(ar, s, valid, ar->width)
	: ft_write_s(ar, (char *)s, valid, len);
	return (count);
}
