/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:37:50 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/12 20:02:11 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

static void		kill_carriage(t_corewar *vm, t_carriage *to_delete)
{
	t_carriage	*cur_carriage;
	t_carriage	*next_carriage;
	
	cur_carriage = vm->start_carriage;
	if (vm->start_carriage == to_delete)
	{
		vm->start_carriage = to_delete->next;
		free(to_delete);
		to_delete = NULL;
		return ;
	}
	while (cur_carriage->next != to_delete)
		cur_carriage = cur_carriage->next;
	next_carriage = cur_carriage->next->next;
	free(cur_carriage->next);
	cur_carriage->next = next_carriage;
}

/*
** a carriage is dead if cycle_to_die is zero or less and
** if it used `live` more than cycle_to_die cycles before
*/
static void		check_carriages(t_carriage *start_carriage, t_corewar *vm)
{
	t_carriage	*cur_carriage;
	t_carriage	*next_carriage;
	
	cur_carriage = start_carriage;
	while (cur_carriage)
	{
		next_carriage = cur_carriage->next;
		if (vm->cycles_to_die <= 0 ||
	vm->total_cycles - cur_carriage->cycle_was_live >= vm->cycles_to_die)
			kill_carriage(vm, cur_carriage);
		cur_carriage = next_carriage;
	}
}

/*
** if live_count more than NBR_LIVE and
** if check_count more than MAX_CHECKS then
** decrease cycle_to_die by CYCLE_DELTA
*/
static void		check_cycle_to_die(t_corewar *vm)
{
	vm->live_count = 0;
	if (vm->live_count > NBR_LIVE || vm->check_count > MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->check_count = 0;
	}
}

void			check(t_corewar *vm)
{
	vm->total_cycles += vm->current_cycles;
	vm->current_cycles = 0;
	vm->check_count++;
    check_carriages(vm->start_carriage, vm);
	check_cycle_to_die(vm);
}
