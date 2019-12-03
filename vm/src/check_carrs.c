/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_carrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 18:03:56 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 20:18:29 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_carr	*remove_carr(t_vm *vm, t_carr *carr)
{
	t_carr	*res;

	res = carr->next;
	if (carr->next)
		res->prev = carr->prev;
	if (carr->prev)
		carr->prev->next = res;
	else
		vm->head = res;
	if (carr)
	{
		free(carr);
		carr = NULL;
	}
	return (res);
}

t_carr	*check_carrs(t_vm *vm, t_carr *carr)
{
	while (carr)
	{
		if (vm->cycles_from_start - carr->lastlive_cycle >
			vm->cycles_to_die || vm->cycles_to_die <= 0)
			carr = remove_carr(vm, carr);
		else
			carr = carr->next;
	}
	carr = vm->head;
	if (vm->live_count_curr >= NBR_LIVE ||
		vm->check_count >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->check_count = 0;
	}
	vm->live_count_curr = 0;
	return (carr);
}
