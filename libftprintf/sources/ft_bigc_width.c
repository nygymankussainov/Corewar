/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigc_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 18:37:02 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:33:30 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			ft_bigc_width(t_spec *argument, int len)
{
	int		n;
	int		taken;

	n = argument->width;
	if (len <= 7)
		taken = 1;
	else if (len <= 11)
		taken = 2;
	else if (len <= 16)
		taken = 3;
	else
		taken = 4;
	if (n - taken > 0)
		return (n - taken);
	return (0);
}
