/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:09:17 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/09 17:31:50 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_itoh(int32_t value, int size, t_major *major)
{
	int		step;
	int		tmp;

	tmp = size;
	step = 0;
	while (size)
	{
		BYTECODE[COL + size - 1] = (u_int8_t)((value >> step) & 0xFF);
		step += 8;
		size--;
	}
	COL += tmp;
}
