/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/25 23:59:44 by screight         ###   ########.fr       */
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
		while (SDL_PollEvent(vm->sdl->e) != 0)
		{
			if ((vm->sdl->e->type == SDL_KEYDOWN && vm->sdl->e->key.keysym.sym == SDLK_ESCAPE))
				exit(0) ;
		}
		if (vm->current_cycles == vm->cycles_to_die)
			check(&vm);
		else
			execute_carriages(&vm);
	}
	display_array(vm->arena, 64, 64);
	ft_printf("\nWinner is %d with name %s\n", vm->winner->id, vm->winner->name);
}
