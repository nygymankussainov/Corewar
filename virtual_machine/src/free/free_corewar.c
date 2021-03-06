/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:14:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/05 17:53:35 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			free_carriage(t_corewar *vm)
{
	t_carriage	*tmp;
	t_carriage	*save_next;

	tmp = vm->start_carriage;
	while (tmp)
	{
		save_next = tmp->next;
		free(tmp);
		tmp = save_next;
	}
	vm->start_carriage = NULL;
}

void			free_corewar(t_corewar *vm)
{
	int			n;
	t_core		*tmp;

	n = 0;
	while (n < vm->number_of_players)
	{
		if (vm->cores[n] && vm->cores[n]->executable_file_name)
			free(vm->cores[n]->executable_file_name);
		if (vm->cores[n])
			free(vm->cores[n]);
		tmp = vm->line_of_players->next;
		if (vm->line_of_players)
			free(vm->line_of_players);
		vm->line_of_players = tmp;
		n++;
	}
	if (vm->start_carriage)
		free_carriage(vm);
	if (vm->sdl)
		free_sdl(vm->sdl);
	free(vm->arg_code);
	free(vm);
}
