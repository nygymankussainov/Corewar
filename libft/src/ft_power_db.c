/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_db.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:30:32 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/07/08 10:19:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double		ft_power_db(long double n, int p)
{
	long double		result;

	result = 1;
	if (p < 0)
	{
		while (p < 0)
		{
			result *= 1 / n;
			p++;
		}
		return (result);
	}
	while (p > 0)
	{
		result *= n;
		p--;
	}
	return (result);
}
