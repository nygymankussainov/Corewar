/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:43:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/01 19:12:34 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ld(t_vm *vm, t_carr *carr, t_player *player)
{
	int		i;
	char	*address;

	player += 0;
	i = 0;
	if (vm->args_type[0] == IND_CODE)
	{
		vm->args[0] %= IDX_MOD;
		if (!(address = (char *)ft_memalloc(sizeof(char) * carr->op->t_dir_size + 1)))
		{
			ft_printf("%s\n", strerror(12));
			exit(12);
		}
		while (i < carr->op->t_dir_size)
		{
			address[i] = vm->arena[(carr->pos + vm->args[0] + i) % MEM_SIZE];
			++i;
		}
		address = rev_bytes(address, carr->op->t_dir_size);
		i = 0;
		while (!address[i])
			++i;
		vm->args[0] = *((int *)(address + i));
		ft_strdel(&address);
	}
	carr->reg[vm->args[1] - 1] = vm->args[0];
	carr->carry = vm->args[0] == 0 ? 1 : 0;
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
