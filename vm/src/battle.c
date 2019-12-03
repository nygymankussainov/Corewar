/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:25:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 20:27:44 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_opcode(t_vm *vm, t_carr *carr)
{
	int32_t		i;

	if (vm->arena[carr->pos % MEM_SIZE] >= vm->first_op
		&& vm->arena[carr->pos % MEM_SIZE] <= vm->last_op)
	{
		i = (int32_t)vm->arena[carr->pos % MEM_SIZE];
		carr->op = &g_ops[i - 1];
		carr->cycles_to_exec = g_ops[i - 1].cycles;
		carr->opcode = vm->arena[carr->pos % MEM_SIZE];
	}
	else
	{
		carr->cycles_to_exec = 0;
		carr->op = NULL;
		carr->opcode = '\0';
	}
}

void	carr_move(t_carr *carr, int step)
{
	carr->pos = (carr->pos + step) % MEM_SIZE;
}

void	review_carrs(t_vm *vm, t_carr *carr)
{
	while (carr)
	{
		if (carr->cycles_to_exec == 0)
			set_opcode(vm, carr);
		if (carr->cycles_to_exec > 0)
			--carr->cycles_to_exec;
		if (carr->cycles_to_exec == 0)
			verify_operation(vm, carr);
		carr = carr->next;
	}
}

void	battle(t_carr *carr, t_vm *vm)
{
	while (vm->cycles_to_die > 0 && carr)
	{
		vm->cycles_to_die_curr = vm->cycles_to_die;
		while (vm->cycles_to_die_curr-- > 0)
		{
			review_carrs(vm, carr);
			carr = vm->head;
			++vm->cycles_from_start;
		}
		++vm->check_count;
		carr = check_carrs(vm, carr);
	}
	carr = check_carrs(vm, carr);
	ft_printf("Contestant %d, \"%s\", has won !\n", \
	vm->lastlive->id, vm->lastlive->name);
}
