/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/22 14:32:05 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				start_war(t_corewar *vm)
{
	t_carriage		*tmp;
	uint8_t			byte_with_command;
	t_operation		op;

	tmp = vm->start_carriage;
	// display_array(vm->arena, 64, 64);
	// ft_putstr("\n\n");
	while (vm->start_carriage)
	{
		if (vm->current_cycles == vm->cycles_to_die)
			check(&vm);
		else
			execute_carriages(&vm);
	}
	display_array(vm->arena, 64, 64);
	ft_printf("\nWinner is %d with name %s\n total_cycles %d", vm->winner->id, vm->winner->name, vm->total_cycles);
}
