/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:37:50 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/05 13:29:27 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void		check_carriages(t_carriage *start_carriage, t_corewar *vm)
{
	t_carriage	*cur_carriage;
	t_carriage	*next_carriage;

	cur_carriage = start_carriage;
	while (cur_carriage)
	{
		next_carriage = cur_carriage->next;
		if (vm->cycles_to_die <= 0 ||
				(int32_t)(vm->total_cycles - cur_carriage->cycle_was_live) >=
														vm->cycles_to_die)
			kill_carriage(&vm, cur_carriage);
		cur_carriage = next_carriage;
	}
}

static void		check_cycle_to_die(t_corewar *vm)
{
	if (vm->live_count >= NBR_LIVE || vm->check_count == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->check_count = 0;
	}
	vm->live_count = 0;
}

void			check(t_corewar **vm)
{
	(*vm)->total_cycles += (*vm)->current_cycles;
	(*vm)->current_cycles = 0;
	(*vm)->check_count++;
	check_carriages((*vm)->start_carriage, (*vm));
	check_cycle_to_die((*vm));
}
