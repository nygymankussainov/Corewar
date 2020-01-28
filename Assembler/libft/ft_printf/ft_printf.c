/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:57:32 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 13:29:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

short		flag_length(char *str, char c)
{
	short	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

void		ft_fill_struct(const char *format, int i, t_flags *s)
{
	char		*str;

	str = ft_strnew(i + 1);
	str = ft_strncpy(str, F, i + 1);
	str[i + 1] = '\0';
	i = 0;
	while (str[i])
	{
		s->prec = str[i] == '.' ? ft_atoi(str + i + 1) : s->prec;
		s->zero_padd = str[i] == '.' ? ft_atoi(str + i + 1) : s->zero_padd;
		s->dot = str[i] == '.' ? 1 : s->dot;
		s->hash = str[i] == '#' ? 1 : s->hash;
		s->zero = str[i] == '0' && !ft_isalpha(str[i + 1]) ? 1 : s->zero;
		s->neg = str[i] == '-' ? 1 : s->neg;
		s->pos = str[i] == '+' ? 1 : s->pos;
		s->bigl = str[i] == 'L' ? 1 : s->bigl;
		s->z = str[i] == 'z' ? 1 : s->z;
		i++;
	}
	s->width += get_width(str);
	s->m = flag_length(str, 'm');
	s->z = s->m ? 0 : s->z;
	s->l = flag_length(str, 'l');
	s->h = flag_length(str, 'h');
	free(str);
}

int			ft_conv(const char **format, va_list valist, t_flags *s)
{
	int		ret;

	ret = 0;
	s->zero = s->neg && (**F == 'f' || **F == 'F') ? 0 : s->zero;
	if (ft_strchr("diouxXpfFDOUb", **F) && *F)
		ret = ft_number(F, valist, s);
	else if (ft_strchr("sc", **F) && **F)
		ret = ft_symbol(F, valist, s);
	else
	{
		s->zero = s->neg ? 0 : s->zero;
		if (s->width && !s->neg)
			ret = print_zero_or_space(--s->width, s->zero, ret);
		ft_putchar(**F);
		if (s->width && s->neg)
			ret = print_zero_or_space(--s->width, s->zero, ret);
		*F += 1;
		ret++;
	}
	free(s);
	return (ret);
}

int			ft_percent(const char **format, va_list valist)
{
	int			i;
	t_flags		*s;

	if (!(s = (t_flags *)ft_memalloc(sizeof(t_flags))))
		return (0);
	i = 0;
	(*F)++;
	find_whitesp(F, s);
	s->whitesp = s->whitesp > 1 ? 1 : s->whitesp;
	s->prec = 6;
	while (ft_strchr(".-+#lLh0123456789mz", *(*F + i)) && *(F + i))
		i++;
	if (i)
		ft_fill_struct(*F, i, s);
	if (find_conv(*F))
		*F += i;
	else
	{
		free(s);
		return (0);
	}
	return (ft_conv(F, valist, s));
}

int			ft_printf(const char *format, ...)
{
	int			ret;
	va_list		valist;

	va_start(valist, F);
	ret = 0;
	while (*F)
	{
		if (*F == '%')
			ret += ft_percent(&F, valist);
		else
		{
			ft_putchar(*F);
			F++;
			ret++;
		}
	}
	va_end(valist);
	return (ret);
}
