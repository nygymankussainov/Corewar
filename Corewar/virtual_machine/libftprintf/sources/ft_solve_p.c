/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:45:36 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:36:22 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					ft_putst(char const *s)
{
	int				count;

	count = 0;
	if (s)
	{
		while (*s && ++count)
		{
			ft_putchar(*s);
			s++;
		}
	}
	return (count);
}

int					ft_write_p(t_spec *arg, int w, char *str, int valid)
{
	int				count;

	count = 0;
	if (*str != '0' || (*str == '0' && arg->precision >= 0))
		count = ft_strlen(str);
	arg->precision = (arg->precision > 0) ? arg->precision - count
	: arg->precision;
	count += (arg->precision > 0) ? arg->precision : 0;
	while (valid == 1 && --w >= 0 && ++count && arg->width >= arg->precision)
		write(1, " ", 1);
	write(1, "0x", 2);
	while (arg->precision > 0)
	{
		write(1, "0", 1);
		arg->precision--;
	}
	if (valid == -1 && !(arg->precision == -1 && *str == '0'))
		ft_putst(str);
	while (valid != 1 && --w >= 0 && ++count && arg->width >= arg->precision)
		write(1, " ", 1);
	if (valid != -1 && !(arg->precision == -1 && *str == '0'))
		ft_putst(str);
	return (count + 2);
}

int					ft_solve_p(t_spec *argument, va_list arg)
{
	unsigned long	addr;
	char			*str;
	int				valid;
	int				len;
	int				count;

	if (!(valid = ft_valid_flags_c_s_p(argument)))
		return (0);
	addr = (unsigned long)va_arg(arg, void *);
	if (!(str = ft_change_system_over_ten(addr, 16, 0)))
		return (0);
	len = ft_strlen(str);
	len = argument->width - len - 2;
	count = ft_write_p(argument, len, str, valid);
	ft_strdel(&str);
	return (count);
}
