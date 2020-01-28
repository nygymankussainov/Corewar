/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:26:56 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/31 18:36:37 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_initial_number(int len, int exp_i, char **n1)
{
	int		i;
	char	*res;
	char	*n2;

	if (!(res = (char *)ft_memalloc(sizeof(char) * (len + 1))) ||
		!(*n1 = (char *)ft_memalloc(sizeof(char) * 16382)))
		return (0);
	ft_bzero(res, len);
	i = 1;
	n2 = ft_itoa_ll(ft_power(5, 0));
	longmulti(n2, "5", n1);
	free(n2);
	while (i++ < -exp_i)
	{
		if (!(n2 = (char *)ft_memalloc(sizeof(char) * ft_strlen(*n1) + 1)))
			return (NULL);
		n2 = ft_strcpy(n2, *n1);
		longmulti(n2, "5", n1);
		free(n2);
	}
	prepare_number(*n1, &res, exp_i);
	return (res);
}

void	calculate_decimal(char *mant, char **res, int exp_i, char **n1)
{
	char	*tmp;
	int		len;

	len = ft_strlen(*res);
	if (!(tmp = (char *)ft_memalloc(sizeof(char) * len + 1)))
		return ;
	ft_bzero(tmp, len);
	while (*mant)
	{
		longmulti(*n1, "5", n1);
		if (*mant == '1')
		{
			prepare_number(*n1, &tmp, exp_i);
			longadd(*res, tmp, res);
			ft_bzero(tmp, len);
		}
		mant++;
		exp_i--;
	}
	free(*n1);
	free(tmp);
}
