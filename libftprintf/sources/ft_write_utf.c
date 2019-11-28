/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_utf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:27:53 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:38:21 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int					ft_three_bytes(unsigned int sym, unsigned char oct, int n,
									int min)
{
	unsigned int	mask3;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;
	unsigned char	o4;

	while (min == 0 && n-- > 0)
		write(1, " ", 1);
	mask3 = 4034953344;
	o4 = (sym << 26) >> 26;
	o3 = ((sym >> 6) << 26) >> 26;
	o2 = ((sym >> 12) << 26) >> 26;
	o1 = ((sym >> 18) << 29) >> 29;
	oct = (mask3 >> 24) | o1;
	write(1, &oct, 1);
	oct = ((mask3 << 8) >> 24) | o2;
	write(1, &oct, 1);
	oct = ((mask3 << 8) >> 24) | o3;
	write(1, &oct, 1);
	oct = ((mask3 << 8) >> 24) | o4;
	write(1, &oct, 1);
	while (min == 1 && n-- > 0)
		write(1, " ", 1);
	return (4);
}

int					ft_two_bytes(unsigned int sym, unsigned char oct, int n,
									int min)
{
	unsigned int	mask2;
	unsigned char	o1;
	unsigned char	o2;
	unsigned char	o3;

	while (min == 0 && n-- > 0)
		write(1, " ", 1);
	mask2 = 14712960;
	o3 = (sym << 26) >> 26;
	o2 = ((sym >> 6) << 26) >> 26;
	o1 = (sym >> 12);
	oct = (mask2 >> 16) | o1;
	write(1, &oct, 1);
	oct = ((mask2 << 24) >> 24) | o2;
	write(1, &oct, 1);
	oct = ((mask2 << 24) >> 24) | o3;
	write(1, &oct, 1);
	while (min == 1 && n-- > 0)
		write(1, " ", 1);
	return (3);
}

int					ft_one_byte(unsigned int sym, unsigned char oct, int n,
									int min)
{
	unsigned int	mask1;
	unsigned char	o1;
	unsigned char	o2;

	while (min == 0 && n-- > 0)
		write(1, " ", 1);
	mask1 = 49280;
	o2 = (sym << 26) >> 26;
	o1 = (sym >> 6);
	oct = (mask1 >> 8) | o1;
	write(1, &oct, 1);
	oct = ((mask1 << 24) >> 24) | o2;
	write(1, &oct, 1);
	while (min == 1 && n-- > 0)
		write(1, " ", 1);
	return (2);
}

int					ft_write_utf(t_spec *argument, long sym, int min)
{
	unsigned char	oct;
	int				len;
	int				n;
	int				ret;

	oct = '\0';
	len = ft_bit_count(sym);
	n = 0;
	if (argument->type != 's' || argument->type != 'S')
		n = (argument->width > 0) ? ft_bigc_width(argument, len) : 0;
	ret = n;
	if (len <= 7)
	{
		while (min == 0 && n-- > 0)
			write(1, " ", 1);
		oct = sym;
		write(1, &oct, 1);
		while (min == 1 && n-- > 0)
			write(1, " ", 1);
		return (1 + ret);
	}
	else if (len <= 11)
		return (ft_one_byte(sym, oct, n, min) + ret);
	return (len <= 16) ? (ft_two_bytes(sym, oct, n, min) + ret) :
	(ft_three_bytes(sym, oct, n, min) + ret);
}
