/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 08:49:11 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 16:23:02 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	xor(t_vm *vm, t_carr *carr)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while (i < carr->op->args_number - 1)
	{
		if (vm->args_type[i] == REG_CODE)
			value = value ? value ^ carr->reg[vm->args[i] - 1]
			: carr->reg[vm->args[i] - 1];
		else if (vm->args_type[i] == DIR_CODE)
			value = value ? value ^ vm->args[i] : vm->args[i];
		else
			value = value ? value ^
			get_ind_value(vm, carr, vm->args[i], 1)
			: get_ind_value(vm, carr, vm->args[i], 1);
		++i;
	}
	carr->reg[vm->args[2] - 1] = value;
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
}

void	or(t_vm *vm, t_carr *carr)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while (i < carr->op->args_number - 1)
	{
		if (vm->args_type[i] == REG_CODE)
			value = value ? value | carr->reg[vm->args[i] - 1]
			: carr->reg[vm->args[i] - 1];
		else if (vm->args_type[i] == DIR_CODE)
			value = value ? value | vm->args[i] : vm->args[i];
		else
			value = value ? value |
			get_ind_value(vm, carr, vm->args[i], 1)
			: get_ind_value(vm, carr, vm->args[i], 1);
		++i;
	}
	carr->reg[vm->args[2] - 1] = value;
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
}

void	and(t_vm *vm, t_carr *carr)
{
	int		i;
	int		value;

	i = 0;
	value = 0;
	while (i < carr->op->args_number - 1)
	{
		if (vm->args_type[i] == REG_CODE)
			value = value ? value & carr->reg[vm->args[i] - 1]
			: carr->reg[vm->args[i] - 1];
		else if (vm->args_type[i] == DIR_CODE)
			value = value ? value & vm->args[i] : vm->args[i];
		else
			value = value ? value &
			get_ind_value(vm, carr, vm->args[i], 1)
			: get_ind_value(vm, carr, vm->args[i], 1);
		++i;
	}
	carr->reg[vm->args[2] - 1] = value;
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
}

void	sub(t_vm *vm, t_carr *carr)
{
	carr->reg[vm->args[2] - 1] = carr->reg[vm->args[0] - 1] - carr->reg[vm->args[1] - 1];
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
}

void	add(t_vm *vm, t_carr *carr)
{
	carr->reg[vm->args[2] - 1] = carr->reg[vm->args[0] - 1] + carr->reg[vm->args[1] - 1];
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
}
