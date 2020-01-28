/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 15:05:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 15:40:06 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_conv_u(const char **format, va_list valist, t_flags *s)
{
	int						ret;
	char					*str;
	unsigned long long		nbr;

	ret = 0;
	if (s->l == 2 || s->conv == 'U')
		nbr = (long long)va_arg(valist, long long);
	else if (s->l == 1)
		nbr = (unsigned long)va_arg(valist, unsigned long);
	else if (s->h == 2)
		nbr = (unsigned char)va_arg(valist, int);
	else if (s->h == 1)
		nbr = (unsigned short)va_arg(valist, unsigned int);
	else
		nbr = va_arg(valist, unsigned int);
	str = ft_uitoa_base(nbr, 10, 'u');
	s->zero = s->zero_padd && s->width ? 0 : s->zero;
	*str = nbr == 0 && !s->zero_padd && s->dot ? '\0' : *str;
	ret = ft_strlen(str);
	ret += width(str, s, ret);
	*F += 1;
	free(str);
	return (ret);
}
