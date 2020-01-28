/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:27:31 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/06 13:28:13 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_string(va_list valist, t_flags *s)
{
	char	*str;
	int		ret;
	int		tmp;

	str = va_arg(valist, char *);
	if (!str)
		str = s->dot && !s->zero_padd ? ft_strdup("(null).") :
			ft_strdup("(null)");
	else
		str = ft_strndup(str, ft_strlen(str));
	*str = s->dot && !s->zero_padd ? '\0' : *str;
	ret = ft_strlen(str);
	if (s->zero_padd && s->zero_padd <= ret)
	{
		str[s->zero_padd] = '\0';
		tmp = ret;
		ret = ret - tmp + ft_strlen(str);
	}
	else
		s->zero_padd = 0;
	if (ret >= s->width)
		ft_putstr(str);
	ret += ret < s->width ? width(str, s, ret) : 0;
	free(str);
	return (ret);
}

int		ft_symbol(const char **format, va_list valist, t_flags *s)
{
	char	*str;
	char	sym;
	int		ret;

	ret = 1;
	s->conv = **F;
	s->zero = 0;
	if (s->conv == 's')
		ret = print_string(valist, s);
	else
	{
		sym = (char)va_arg(valist, int);
		str = ft_strnew(1);
		str[0] = sym;
		if (ret >= s->width || ((s->neg || ret >= s->width)
			&& !sym && s->width))
			ft_putchar(sym);
		ret += ret < s->width ? width(str, s, ret) : 0;
		if (!sym && s->width && (ret <= s->width || !s->neg))
			write(1, &sym, 1);
		free(str);
	}
	*F += 1;
	return (ret);
}
