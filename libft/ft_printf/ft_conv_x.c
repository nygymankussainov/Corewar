/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:53:37 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 12:09:10 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	get_nbr_x(const char **format, va_list valist,
	t_flags *s, char **str)
{
	long long	nbr;

	s->conv = **F;
	if (s->l == 2)
		nbr = (unsigned long long)va_arg(valist, unsigned long long);
	else if (s->l == 1)
		nbr = (unsigned long)va_arg(valist, unsigned long);
	else if (s->h == 2)
		nbr = (unsigned char)va_arg(valist, int);
	else if (s->h == 1)
		nbr = (unsigned short)va_arg(valist, unsigned int);
	else
		nbr = va_arg(valist, unsigned int);
	if (**F == 'x')
		*str = ft_uitoa_base(nbr, 16, 'x');
	else
		*str = ft_uitoa_base(nbr, 16, 'X');
	return (nbr);
}

void		write_or_join(char **str, char conv, char key)
{
	if (key == 'w')
	{
		if (conv == 'X')
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
	else if (key == 'j')
	{
		if (conv == 'X')
			*str = ft_strjoin("0X", *str, 0, 1);
		else
			*str = ft_strjoin("0x", *str, 0, 1);
	}
}

int			print_0x(char **str, t_flags *s, int ret, long long nbr)
{
	int		tmp;

	tmp = 0;
	if ((s->hash && nbr != 0) || (s->hash && ret >= s->width && nbr != 0))
	{
		if ((ret >= s->width && nbr != 0) || (((s->zero_padd && s->zero_padd >
			ft_count_digit_ll(nbr, 1)) || s->zero) && s->width && s->hash))
		{
			if (s->width && s->hash)
				s->width -= 2;
			if (s->width && s->zero_padd && s->hash && !s->neg)
			{
				ft_putchar(' ');
				s->width--;
				tmp++;
			}
			tmp += 2;
			write_or_join(str, s->conv, 'w');
		}
		else
			write_or_join(str, s->conv, 'j');
	}
	return (tmp);
}

int			ft_conv_x(const char **format, va_list valist, t_flags *s)
{
	int						ret;
	int						tmp;
	char					*str;
	long long				nbr;

	ret = 0;
	tmp = 0;
	nbr = get_nbr_x(F, valist, s, &str);
	*str = nbr == 0 && !s->zero_padd && s->dot ? '\0' : *str;
	s->neg = s->hash && s->width && ft_count_digit_ll(nbr, 1) >= s->width
		? 0 : s->neg;
	s->width = s->hash && s->width && ft_count_digit_ll(nbr, 1) >= s->width
		? 0 : s->width;
	s->zero = s->zero_padd || (s->hash && s->zero && s->neg) ? 0 : s->zero;
	ret = s->hash && nbr != 0 ? ft_strlen(str) + 2 : ft_strlen(str);
	tmp = print_0x(&str, s, ret, nbr);
	ret = manage_width(str, s) + tmp;
	*F += 1;
	free(str);
	return (ret);
}
