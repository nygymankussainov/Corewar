/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:16:18 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/04 20:54:29 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	copy_carr(t_vm *vm, t_carr *curr)
{
	int		i;

	i = 0;
	create_carriage(&vm->head);
	while (i < REG_NUMBER)
	{
		vm->head->reg[i] = curr->reg[i];
		++i;
	}
	vm->head->carry = curr->carry;
	vm->head->lastlive_cycle = curr->lastlive_cycle;
}

void	lfork(t_vm *vm, t_carr *carr)
{
	int		pos;

	copy_carr(vm, carr);
	pos = get_pos(carr->pos - carr->skip + vm->args[0]);
	vm->head->pos = pos;
}

void	lldi(t_vm *vm, t_carr *carr)
{
	int		value;
	int		pos;
	int		i;

	i = 0;
	pos = 0;
	while (i < carr->op->args_number - 1)
	{
		if (vm->args_type[i] == REG_CODE)
			pos += carr->reg[vm->args[i] - 1];
		else if (vm->args_type[i] == DIR_CODE)
			pos += vm->args[i];
		else
			pos += get_ind_value(vm, carr, vm->args[i], 1);
		++i;
	}
	value = get_ind_value(vm, carr, pos, 0);
	carr->reg[vm->args[i] - 1] = value;
}

void	lld(t_vm *vm, t_carr *carr)
{
	int		i;

	i = 0;
	if (vm->args_type[0] == IND_CODE)
		vm->args[0] = get_ind_value(vm, carr, vm->args[0], 0);
	carr->reg[vm->args[1] - 1] = vm->args[0];
	carr->carry = carr->reg[vm->args[1] - 1] == 0 ? 1 : 0;
}

void	ffork(t_vm *vm, t_carr *carr)
{
	int		pos;
	
	copy_carr(vm, carr);
	pos = vm->args[0] % IDX_MOD;
	pos = get_pos(carr->pos - carr->skip + pos);
	vm->head->pos = pos;
}
