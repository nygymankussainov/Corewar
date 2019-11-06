/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:08 by egiant            #+#    #+#             */
/*   Updated: 2019/11/01 16:15:10 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*void		init_arena(t_corewar *vm)
{

}*/

void			init_core(t_core *player)
{
	player->id = 0;
	player->exec_code_size = 0;
	player->next = NULL;
}

t_corewar		*init_vm(void)
{
	int			n;
	t_corewar	*vm;

	n = -1;
	vm = (t_corewar *)malloc(sizeof(t_corewar));
	vm->line_of_players = NULL;
	while (++n < 4)
		vm->cores[n] = NULL;
	vm->number_of_players = 0;
	return(vm);
}