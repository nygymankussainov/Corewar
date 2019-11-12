/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/12 20:04:04 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				start_war(t_corewar *vm)
{
	t_carriage		*tmp;
	uint8_t			byte_with_command;
	t_operation		op;

	tmp = vm->start_carriage;
	while (vm->start_carriage)
	{
		if (vm->current_cycles == vm->cycles_to_die)
			check(vm);
		else
			execute_carriages(vm);
	}
}


/*
T_REG 01
T_DIR 10
T_IND 11

op_live
op_ld
op_st
op_add
op_sub
op_and
op_or
op_xor
op_zjmp
op_ldi
op_sti
op_fork
op_lld
op_lldi
op_lfork
op_aff

*/