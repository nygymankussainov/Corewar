/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 19:27:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/03 12:06:52 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_width(char *str)
{
	int width;
	int	i;

	i = 0;
	while (*str && *str != '.')
	{
		if (ft_isdigit(*str))
		{
			while (str[i] && str[i] != '.' && !ft_isalpha(str[i]))
			{
				if (str[i] == '-' || str[i] == '+')
				{
					width = ft_atoi(str + i + 1);
					width = width < 0 ? -width : width;
					return (width);
				}
				i++;
			}
			width = ft_atoi(str);
			width = width < 0 ? -width : width;
			return (width);
		}
		str++;
	}
	return (0);
}

void	put_zero_or_space(char **str, int width, int zero)
{
	while (width > 0 && width--)
	{
		if (zero)
		{
			if ((*str)[0] == '-' || (*str)[0] == '+')
			{
				if ((*str)[0] == '-')
					write(1, "-", 1);
				else
					write(1, "+", 1);
				(*str)++;
			}
			ft_putchar('0');
		}
		else
			ft_putchar(' ');
	}
}

void	put_zero_padding(char **str, int zero_padd)
{
	while (zero_padd > 0 && zero_padd--)
	{
		if ((*str)[0] == '-' || (*str)[0] == '+')
		{
			if ((*str)[0] == '-')
				write(1, "-", 1);
			else
				write(1, "+", 1);
			(*str)++;
		}
		ft_putchar('0');
	}
}

void	manage_order_and_print(char *str, t_flags *s)
{
	if (!s->neg)
	{
		put_zero_or_space(&str, s->width, s->zero);
		if (s->neg && !s->pos && !s->zero_padd)
			ft_putstr(str);
		put_zero_padding(&str, s->zero_padd);
		if (s->pos || !s->neg)
			ft_putstr(str);
	}
	else
	{
		put_zero_padding(&str, s->zero_padd);
		if ((s->neg && !s->pos) || (s->neg && s->pos))
			ft_putstr(str);
		put_zero_or_space(&str, s->width, s->zero);
		if (s->pos && !s->neg)
			ft_putstr(str);
	}
}

int		width(char *str, t_flags *s, int len)
{
	int		ret;

	ret = 0;
	if (s->pos && s->sign > 0 && !s->width)
		write(1, "+", 1);
	if (s->sign < 0 && !s->width)
		write(1, "-", 1);
	ret += (s->pos && s->sign > 0 && !s->width) ||
		(s->sign < 0 && !s->width) ? 1 : 0;
	s->zero_padd += (s->pos && s->neg) || (s->zero_padd > 0 &&
		s->sign < 0 && s->width) ? 1 : 0;
	s->zero_padd += s->pos && !s->neg && s->width && s->sign > 0 ? 1 : 0;
	s->zero_padd -= s->zero_padd > 0 ? len : 0;
	s->width -= s->zero_padd > 0 ? len + s->zero_padd : len;
	ret = s->width > 0 ? s->width : ret;
	ret += s->zero_padd > 0 ? s->zero_padd : 0;
	manage_order_and_print(str, s);
	return (ret);
}
