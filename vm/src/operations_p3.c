/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:16:18 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 13:23:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	copy_carr(t_carr *head, t_carr *curr)
{
	int		i;

	i = 0;
	create_carriage(&head);
	while (i < REG_NUMBER)
	{
		head->reg[i] = curr->reg[i];
		++i;
	}
	head->carry = curr->carry;
	head->lastlive_cycle = curr->lastlive_cycle;
}

void	lfork(t_vm *vm, t_carr *carr)
{
	copy_carr(vm->head, carr);
	vm->head->pos = vm->args[0] % MEM_SIZE;
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
			pos += get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE);
		++i;
	}
	value = get_ind_value(vm, carr, pos, REG_SIZE);
	carr->reg[vm->args[i] - 1] = value;
}

void	lld(t_vm *vm, t_carr *carr)
{
	int		i;

	i = 0;
	if (vm->args_type[0] == IND_CODE)
		vm->args[0] = get_ind_value(vm, carr, vm->args[0], REG_SIZE);
	carr->reg[vm->args[1] - 1] = vm->args[0];
	carr->carry = carr->reg[vm->args[1] - 1] == 0 ? 1 : 0;
}

void	ffork(t_vm *vm, t_carr *carr)
{
	copy_carr(vm->head, carr);
	vm->head->pos = vm->args[0] % IDX_MOD;
}
