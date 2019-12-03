/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh_vm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:09:17 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 15:29:29 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_itoh_vm(int32_t value, int size, t_vm *vm, int pos)
{
	int		step;
	int		tmp;

	tmp = size;
	step = 0;
	while (size)
	{
		vm->arena[pos + size - 1] = (u_int8_t)((value >> step) & 0xFF);
		step += 8;
		size--;
	}
}