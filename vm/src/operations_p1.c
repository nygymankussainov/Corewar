/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:43:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/02 10:28:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ldi(t_vm *vm, t_carr *carr, t_player *player)
{
	int		value;
	int		pos;
	int		i;

	i = 0;
	pos = 0;
	player += 0;
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
	value = get_ind_value(vm, carr, pos % IDX_MOD, REG_SIZE);
	carr->reg[vm->args[i] - 1] = value;
	return (0);
}

int		zjmp(t_vm *vm, t_carr *carr, t_player *player)
{
	player += 0;
	if (carr->carry)
		carr->pos = (carr->pos + vm->args[0]) % IDX_MOD;
	return (0);
}

int		st(t_vm *vm, t_carr *carr, t_player *player)
{
	player += 0;
	if (vm->args_type[1] == REG_CODE)
		carr->reg[vm->args[1] - 1] = carr->reg[vm->args[0] - 1];
	else
	{
		vm->args[1] %= IDX_MOD;
		vm->arena[(carr->pos + vm->args[1]) % MEM_SIZE] = carr->reg[vm->args[0] - 1];
		// ft_itoh_vm(carr->reg[vm->args[0] - 1], 1, vm, (carr->pos + vm->args[1]) % MEM_SIZE);
	}
	return (0);
}

int		ld(t_vm *vm, t_carr *carr, t_player *player)
{
	int		i;

	player += 0;
	i = 0;
	if (vm->args_type[0] == IND_CODE)
		vm->args[0] = get_ind_value(vm, carr, vm->args[0] % IDX_MOD, REG_SIZE);
	carr->reg[vm->args[1] - 1] = vm->args[0];
	carr->carry = carr->reg[vm->args[1] - 1] == 0 ? 1 : 0;
	return (0);
}

int		live(t_vm *vm, t_carr *carr, t_player *player)
{
	++carr->live_count;
	++vm->live_count;
	carr->lastlive_cycle = vm->cycles_from_start;
	vm->args[0] *= -1;
	if (vm->args[0] >= 1 && vm->args[0] <= vm->pl_nb)
	{
		vm->lastlive = &player[vm->args[0] - 1];
		++player[vm->args[0] - 1].live_count;
	}
	return (0);
}
