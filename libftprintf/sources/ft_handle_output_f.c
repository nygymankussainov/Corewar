/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_output_f.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:17:18 by screight          #+#    #+#             */
/*   Updated: 2019/08/05 22:35:14 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_krasivo(char *num)
{
	int		i;
	int		tmp;
	int		len;
	int		trig;

	len = 15;
	trig = 0;
	i = 0;
	while (num[i] != '.')
		i++;
	i++;
	tmp = i;
	while (len--)
	{
		if (num[++i] != '0')
		{
			trig = 1;
			break ;
		}
	}
	if (trig == 1 && num[tmp] == '5')
		num[tmp] = num[tmp] + 1;
	else if (trig == 0 && num[tmp] == '5')
		num[tmp] = (num[tmp - 2] - '0') % 2 != 0 ? num[tmp] + 1 : num[tmp] - 1;
}

char		*ft_round(char *num)
{
	int		i;
	int		len;

	i = 0;
	while (num[i])
		i++;
	len = i - 1;
	if (num[--i] >= 5 + '0')
	{
		num[i] = '0';
		while (num[i - 1] == '9' || num[i - 1] == '.')
		{
			if (num[i - 1] != '.')
				num[--i] = '0';
			else
				i--;
		}
		i--;
		if (num[i] == '.')
			i--;
		num[i] = (num[i] + 1);
	}
	num[len] = '\0';
	return (num);
}

int			ft_output_f(char *snum, t_spec *argument, int sign, int z)
{
	int		len;
	int		i;
	int		digits;
	int		n;

	i = 0;
	if (argument->precision == 0)
		ft_krasivo(snum);
	len = argument->precision + 1;
	while (snum[i++] != '.')
		len++;
	snum[len + 1] = '\0';
	snum = ft_round(snum);
	if (snum[1] == '0')
		z++;
	if (sign == -1)
		snum[z] = '-';
	else
		z++;
	if (!(i = ft_valid_flags(argument, 0)))
		return (-1);
	digits = ft_count_digits(snum + z);
	n = ft_write_f(argument, snum + z, digits, i);
	ft_strdel(&snum);
	return (n);
}
