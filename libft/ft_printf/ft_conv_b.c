/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:38:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/04 17:39:51 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_sign(int bigl, char *binary)
{
	if (bigl)
		ft_putchar(binary[48]);
	else
		ft_putchar(binary[0]);
}

int		ft_conv_b(t_flags *s, t_f f)
{
	int		ret;

	if (s->m == 1)
		ft_putstr(f.exp);
	else if (s->m == 2)
		ft_putstr(f.mant);
	else if (s->z)
		print_sign(s->bigl, f.binary);
	else
	{
		print_sign(s->bigl, f.binary);
		ft_putchar('.');
		ft_putstr(f.exp);
		ft_putchar('.');
		ft_putstr(f.mant);
	}
	ret = ft_strlen(f.binary) + 2;
	ret -= s->bigl ? 48 : 0;
	ret = s->m == 1 ? ft_strlen(f.exp) : ret;
	ret = s->m == 2 && !s->bigl ? ft_strlen(f.mant) : ret;
	ret = s->m == 2 && s->bigl ? ft_strlen(f.mant) + 1 : ret;
	ret = s->z ? 1 : ret;
	return (ret);
}
