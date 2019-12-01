/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:25:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/01 16:27:26 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_opcode(t_vm *vm, t_carr *carr)
{
	int32_t		i;

	if (vm->arena[carr->pos] >= vm->first_op
		&& vm->arena[carr->pos] <= vm->last_op)
	{
		i = (int32_t)vm->arena[carr->pos];
		carr->op = &g_ops[i - 1];
		carr->cycles_to_exec = g_ops[i - 1].cycles;
	}
	else
	{
		carr->cycles_to_exec = 0;
		carr->op = NULL;
	}
	carr->opcode = vm->arena[carr->pos];
}

void	carr_move(t_carr *carr, int step)
{
	carr->pos = (carr->pos + step) % MEM_SIZE;
}

void	review_carrs(t_vm *vm, t_carr *carr, t_player *player)
{
	while (carr)
	{
		if (carr->cycles_to_exec == 0)
			set_opcode(vm, carr);
		if (carr->cycles_to_exec > 0)
			--carr->cycles_to_exec;
		if (carr->cycles_to_exec == 0)
			verify_operation(vm, carr, player);
		carr = carr->next;
	}
}

void	battle(t_carr *carr, t_player *player, t_vm *vm)
{
	player += 0;
	while (vm->cycles_to_die > 0 && carr)
	{
		vm->cycles_to_die_curr = vm->cycles_to_die;
		while (vm->cycles_to_die_curr-- > 0)
		{
			review_carrs(vm, carr, player);
			++vm->cycles_from_start;
		}
		++vm->check_count;
		// vm->cycles_to_die = check(vm, carr);
	}
}
