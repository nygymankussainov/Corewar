/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:54:42 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/05 19:40:02 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp(t_vm *vm, t_carr *carr)
{
	int		pos;
	int		skip;

	pos = vm->args[0] % IDX_MOD;
	pos = get_pos(carr->pos - carr->skip + pos);
	if (carr->carry)
		carr->pos = pos;
	else
	{
		skip = skip_args(vm, carr, carr->op->args_number, 1);
		carr_move(carr, skip);
	}
}

void	live(t_vm *vm, t_carr *carr)
{
	++carr->live_count;
	++vm->live_count;
	++vm->live_count_curr;
	carr->lastlive_cycle = vm->cycles_from_start;
	vm->args[0] *= -1;
	if (vm->args[0] >= 1 && vm->args[0] <= vm->pl_nb)
	{
		vm->lastlive = &vm->player[vm->args[0] - 1];
		++vm->player[vm->args[0] - 1].live_count;
		if (vm->l)
		{
			ft_printf("A process shows that player %d (%s) is alive\n", \
			vm->player[vm->args[0] - 1].id, vm->player[vm->args[0] - 1].name);
		}
	}
}

void	aff(t_vm *vm, t_carr *carr)
{
	char	symbol;

	if (!vm->aff)
		return ;
	symbol = (char)carr->reg[vm->args[0] - 1];
	ft_printf("Aff: %c\n", symbol);
}
