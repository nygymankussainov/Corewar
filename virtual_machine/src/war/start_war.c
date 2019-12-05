/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/05 17:44:46 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				announce_winner(t_corewar *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->winner->id,
					vm->winner->name);
}

void				start_war(t_corewar *vm)
{
	t_carriage		*tmp;

	tmp = vm->start_carriage;
	while (vm->start_carriage)
	{
		if (vm->dumps == (int32_t)(vm->current_cycles + vm->total_cycles))
		{
			display_array(vm->arena, 128, 32);
			free_corewar(vm);
			exit(0);
		}
		execute_carriages(&vm);
		if ((int32_t)(vm->current_cycles) == vm->cycles_to_die
					|| vm->cycles_to_die <= 0)
			check(&vm);
	}
	announce_winner(vm);
	if (vm->visual)
		annonce_winner_vis(vm);
}
