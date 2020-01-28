/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ignored_zero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 16:57:14 by egiant            #+#    #+#             */
/*   Updated: 2019/08/05 22:35:31 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void		ft_ignored_zero(t_spec *argument)
{
	int		i;
	int		j;

	i = 0;
	while (argument->flags[i])
	{
		j = 0;
		if (argument->flags[i] == '-' && argument->flags[j])
		{
			while (argument->flags[j])
			{
				if (argument->flags[j] == '0')
				{
					argument->flags[j] = 'x';
					break ;
				}
				else
					j++;
			}
		}
		i++;
	}
}
