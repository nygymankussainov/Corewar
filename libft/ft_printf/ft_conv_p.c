/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:50:18 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 13:48:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_conv_p(const char **format, va_list valist, t_flags *s)
{
	int						ret;
	char					*str;
	void					*ptr;

	ret = 0;
	ptr = va_arg(valist, void *);
	str = ft_itoa_base((long long int)ptr, 16);
	str[2] = ptr == 0 && !s->width && s->dot ? '\0' : str[2];
	ret = ft_strlen(str);
	if (s->width < ret && s->zero_padd)
	{
		write(1, "0x", 2);
		s->zero_padd -= !ft_strcmp(str, "0x") ? 0 : ret - 2;
		ret += s->zero_padd > 0 ? s->zero_padd : 0;
		while (s->zero_padd > 0 && s->zero_padd--)
			ft_putchar('0');
		ft_putstr(str + 2);
	}
	else
		ret += width(str, s, ret);
	*F += 1;
	free(str);
	return (ret);
}
