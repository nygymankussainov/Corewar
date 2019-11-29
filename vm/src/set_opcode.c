/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_opcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:51:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/29 17:12:36 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_opcode(t_major *major, t_carr *carr)
{
	int32_t		i;
	u_int8_t 	a = g_ops[0].opcode;
	u_int8_t 	b = g_ops[OP_NUMBER - 1].opcode;

	if (major->arena[carr->pos] >= a && major->arena[carr->pos] <= b)
	{
		i = (int32_t)major->arena[carr->pos];
		carr->op = &g_ops[i - 1];
		carr->cycles_to_exec = g_ops[i - 1].cycles;
	}
	else
	{
		carr->cycles_to_exec = 0;
		carr->op = 0;
	}
	carr->opcode = major->arena[carr->pos];
}
