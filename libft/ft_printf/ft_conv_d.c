/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:43:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 15:39:22 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	get_nbr_d(const char **format, va_list valist, t_flags *s)
{
	long long	nbr;

	s->conv = **F;
	if (s->l == 2 || s->conv == 'D')
		nbr = (long long)va_arg(valist, long long);
	else if (s->l == 1)
		nbr = (long)va_arg(valist, long);
	else if (s->h == 2)
		nbr = (char)va_arg(valist, int);
	else if (s->h == 1)
		nbr = (short)va_arg(valist, int);
	else
		nbr = (long long)va_arg(valist, int);
	return (nbr);
}

int			ifwhitesp(t_flags *s, int *tmp, int key, int ret)
{
	if (s->whitesp && s->zero_padd && s->width > ret
		&& s->zero_padd > ret && s->zero_padd > s->width)
	{
		(*tmp)++;
		ft_putchar(' ');
	}
	if (s->whitesp && (s->width <= ret || s->neg ||
		(key && !s->zero_padd) || (s->width && s->zero))
		&& s->sign > 0 && !s->pos)
	{
		write(1, " ", 1);
		if (s->neg && s->width > ret)
		{
			s->width -= s->zero_padd ? 1 : 0;
			ret += !s->zero_padd ? 1 : 0;
			(*tmp) += s->zero_padd ? 1 : 0;
		}
		else if (s->width && s->zero && !key)
			ret += s->width > ret ? 1 : 0;
		else if (key)
			(*tmp) += s->width > ret ? 1 : 0;
	}
	return (ret);
}

int			manage_width(char *str, t_flags *s)
{
	int		ret;
	int		tmp;
	int		key;

	tmp = 0;
	key = 0;
	if (!s->width && s->zero_padd && !s->zero)
	{
		if (s->sign < 0 || s->pos > 0)
		{
			if (s->sign < 0)
				write(1, "-", 1);
			else
				write(1, "+", 1);
			tmp++;
		}
		s->width = s->zero_padd;
		s->zero_padd = 0;
		s->zero = 1;
		key = 1;
	}
	ret = ifwhitesp(s, &tmp, key, ft_strlen(str));
	s->whitesp = s->width > ret || s->pos || s->sign < 0 ? 0 : s->whitesp;
	ret += width(str, s, ret) + tmp + s->whitesp;
	return (ret);
}

int			ft_conv_d(const char **format, va_list valist, t_flags *s)
{
	int						ret;
	char					*str;
	__int128_t				nbr;

	nbr = get_nbr_d(F, valist, s);
	s->sign = nbr < 0 ? -1 : 1;
	nbr = s->sign < 0 ? -nbr : nbr;
	str = ft_itoa_ll(nbr);
	s->zero = s->zero_padd || (s->neg && s->zero) ? 0 : s->zero;
	*str = nbr == 0 && !s->zero_padd && s->dot ? '\0' : *str;
	s->pos = s->neg && s->pos && s->sign < 0 ? 0 : s->pos;
	str = s->sign < 0 && s->width ? ft_strjoin("-", str, 0, 1) : str;
	str = (s->pos && s->neg) || (s->pos && !s->neg && s->width && s->sign > 0) ?
		ft_strjoin("+", str, 0, 1) : str;
	ret = manage_width(str, s);
	*F += 1;
	free(str);
	return (ret);
}
