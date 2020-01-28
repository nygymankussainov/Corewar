/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_for_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 15:46:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/01 12:49:30 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_zero_or_space(int width, int zero, int ret)
{
	if (width > 0)
	{
		ret += width;
		while (width--)
		{
			if (!zero)
				ft_putchar(' ');
			else
				ft_putchar('0');
		}
	}
	return (ret);
}

int		width_for_f(char *str, t_flags *s, int ret)
{
	if (s->pos && s->zero)
		write(1, "+", 1);
	else if (s->neg)
	{
		if (s->pos)
			write(1, "+", 1);
		ft_putstr(str);
	}
	s->width -= ret;
	ret = print_zero_or_space(s->width, s->zero, ret);
	if ((s->pos && !s->neg) || (!s->pos && !s->neg))
	{
		if (s->pos && !s->neg && !s->zero)
			write(1, "+", 1);
		ft_putstr(str);
	}
	return (ret);
}
