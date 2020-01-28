/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 14:51:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 15:39:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_conv_o(const char **format, va_list valist, t_flags *s)
{
	int						ret;
	char					*str;
	unsigned long long		nbr;

	ret = 0;
	if (s->l == 2 || s->conv == 'O')
		nbr = (long long)va_arg(valist, long long);
	else if (s->l == 1)
		nbr = (long)va_arg(valist, long);
	else if (s->h == 2)
		nbr = (unsigned char)va_arg(valist, int);
	else if (s->h == 1)
		nbr = (unsigned short)va_arg(valist, unsigned int);
	else
		nbr = va_arg(valist, unsigned int);
	str = ft_uitoa_base(nbr, 8, 'o');
	*str = nbr == 0 && !s->zero_padd && s->dot ? '\0' : *str;
	if (s->hash && (nbr != 0 || (s->dot && nbr == 0)))
		str = ft_strjoin("0", str, 0, 1);
	s->zero = s->zero_padd || (s->neg && s->zero) ? 0 : s->zero;
	ret = s->hash ? ft_strlen(str) + 1 : ft_strlen(str);
	ret = manage_width(str, s);
	*F += 1;
	free(str);
	return (ret);
}
