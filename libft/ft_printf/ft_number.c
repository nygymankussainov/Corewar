/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 14:20:32 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 15:49:18 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_number(const char **format, va_list valist, t_flags *s)
{
	int		ret;

	ret = 0;
	s->conv = **F;
	if (**F == 'd' || **F == 'D' || **F == 'i')
		ret = ft_conv_d(F, valist, s);
	else if (**F == 'x' || **F == 'X')
		ret = ft_conv_x(F, valist, s);
	else if (**F == 'o' || **F == 'O')
		ret = ft_conv_o(F, valist, s);
	else if (**F == 'u' || **F == 'U')
		ret = ft_conv_u(F, valist, s);
	else if (**F == 'p')
		ret = ft_conv_p(F, valist, s);
	else if (**F == 'f' || **F == 'F' || **F == 'b')
		ret = ft_conv_f(F, valist, s);
	return (ret);
}
