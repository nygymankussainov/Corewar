/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:54:42 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 13:24:15 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp(t_vm *vm, t_carr *carr)
{
	if (carr->carry)
		carr->pos = (carr->pos + vm->args[0]) % IDX_MOD;
}

void	live(t_vm *vm, t_carr *carr)
{
	++carr->live_count;
	++vm->live_count;
	carr->lastlive_cycle = vm->cycles_from_start;
	vm->args[0] *= -1;
	if (vm->args[0] >= 1 && vm->args[0] <= vm->pl_nb)
	{
		vm->lastlive = &vm->player[vm->args[0] - 1];
		++vm->player[vm->args[0] - 1].live_count;
	}
}

void	aff(t_vm *vm, t_carr *carr)
{
	char	symbol;

	symbol = (char)carr->reg[vm->args[0] - 1];
	write(1, &symbol, 1);
}
