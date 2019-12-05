/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_interaction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:13:54 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/05 17:43:36 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			kill_carriage(t_corewar **vm, t_carriage *to_delete)
{
	t_carriage	*cur_carriage;
	t_carriage	*next_carriage;

	(*vm)->carriage_count--;
	cur_carriage = (*vm)->start_carriage;
	if ((*vm)->start_carriage == to_delete)
	{
		(*vm)->start_carriage = to_delete->next;
		free(to_delete);
		to_delete = NULL;
		return ;
	}
	while (cur_carriage->next != to_delete)
		cur_carriage = cur_carriage->next;
	next_carriage = cur_carriage->next->next;
	free(cur_carriage->next);
	cur_carriage->next = next_carriage;
	if ((*vm)->visual && (*vm)->sdl->sound)
		Mix_PlayChannel(-1, (*vm)->sdl->dead_car, 0);
}

t_carriage		*copy_carriage(t_corewar *vm, t_carriage *to_copy)
{
	t_carriage	*new_carriage;
	int			i;

	i = 0;
	new_carriage = init_carriage(vm, to_copy->player);
	new_carriage->carry = to_copy->carry;
	new_carriage->cycle_was_live = to_copy->cycle_was_live;
	while (i < REG_NUMBER)
	{
		new_carriage->registers[i] = to_copy->registers[i];
		i++;
	}
	new_carriage->next = vm->start_carriage;
	vm->start_carriage = new_carriage;
	return (new_carriage);
}
