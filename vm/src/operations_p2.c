/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 08:49:11 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/02 10:21:41 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		xor(t_vm *vm, t_carr *carr, t_player *player)
{
	int		i;
	int		value;

	i = 0;
	player += 0;
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
			get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE)
			: get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE);
		++i;
	}
	carr->reg[vm->args[2] - 1] = value;
	return (0);
}

int		or(t_vm *vm, t_carr *carr, t_player *player)
{
	int		i;
	int		value;

	i = 0;
	player += 0;
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
			get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE)
			: get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE);
		++i;
	}
	carr->reg[vm->args[2] - 1] = value;
	return (0);
}

int		and(t_vm *vm, t_carr *carr, t_player *player)
{
	int		i;
	int		value;

	i = 0;
	player += 0;
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
			get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE)
			: get_ind_value(vm, carr, vm->args[i] % IDX_MOD, REG_SIZE);
		++i;
	}
	carr->reg[vm->args[2] - 1] = value;
	return (0);
}

int		sub(t_vm *vm, t_carr *carr, t_player *player)
{
	player += 0;
	carr->reg[vm->args[2] - 1] = carr->reg[vm->args[0] - 1] - carr->reg[vm->args[1] - 1];
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
	return (0);
}

int		add(t_vm *vm, t_carr *carr, t_player *player)
{
	player += 0;
	carr->reg[vm->args[2] - 1] = carr->reg[vm->args[0] - 1] + carr->reg[vm->args[1] - 1];
	carr->carry = carr->reg[vm->args[2] - 1] == 0 ? 1 : 0;
	return (0);
}
