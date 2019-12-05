/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_player_to_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:06:42 by egiant            #+#    #+#             */
/*   Updated: 2019/12/04 18:17:02 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			add_player_to_list(t_corewar *vm, t_core *new_player)
{
	t_core		*core_tmp;

	if (new_player->id == 0)
	{
		core_tmp = vm->line_of_players;
		while (core_tmp->next)
			core_tmp = core_tmp->next;
		core_tmp->next = new_player;
	}
	else
	{
		new_player->next = vm->line_of_players;
		vm->line_of_players = new_player;
	}
}
