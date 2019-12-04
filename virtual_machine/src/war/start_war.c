/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/04 16:28:12 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				start_war(t_corewar *vm)
{
	t_carriage		*tmp;
	uint8_t			byte_with_command;
	t_operation		op;

	tmp = vm->start_carriage;
	while (vm->start_carriage)
	{
		if (vm->dumps != vm->cycles_to_die && vm->dumps == vm->current_cycles + vm->total_cycles)
		{
			display_array(vm->arena, 64, 64);
			free_corewar(vm);
			exit (0);
		}
		execute_carriages(&vm);
		if (vm->current_cycles == vm->cycles_to_die || vm->cycles_to_die <= 0)
			check(&vm);
	}
	if (vm->visual)
	{
		vis_corewar(vm);
		stringColor(vm->sdl->ren, SZX - 250, SZY - 56, 
										vm->winner->name, vm->winner->color);
		SDL_RenderPresent(vm->sdl->ren);
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->winner->id, vm->winner->name, vm->total_cycles);
}
