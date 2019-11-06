/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:08 by egiant            #+#    #+#             */
/*   Updated: 2019/11/02 21:45:42 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		init_carriage(t_corewar *vm)
{
	int8_t		i;
	t_carriage	*cur_carriage;
	t_carriage	*new_carriage;

	i = vm->number_of_players - 1;
	cur_carriage = vm->start_carriage;
	while (i > -1)
	{
		cur_carriage->id = i;
		cur_carriage->carry = false;
		cur_carriage->operation = 0;
		cur_carriage->registers[0] = -i;
		// add carriage position
		if (i != 0)
		{
			if (!(new_carriage = (t_carriage*)malloc(sizeof(t_carriage))))
				termination_with_perror("Error", ENOMEM);
			cur_carriage->next = new_carriage;
			cur_carriage = cur_carriage->next;
		}
		cur_carriage->next = NULL;
		i--;
	}
}

void		set_exec_code(uint8_t *arena, uint16_t position, t_core *core)
{
	uint16_t	i;

	i = 0;
	while (i < core->exec_code_size)
	{
		arena[position + i] = core->exec_code[i];
		i++;
	}
}

void		init_arena(t_corewar *vm)
{
	uint8_t		i;
	uint16_t	cur_position;
	uint16_t	position_step;

	i = 0;
	cur_position = 0;
	position_step = MEM_SIZE / vm->number_of_players;
	while (i < vm->number_of_players)
	{
		set_exec_code(vm->arena, cur_position, vm->cores[i]);
		cur_position += position_step;
		i++;
	}
}

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

	n = MAX_PLAYERS;
	if (!(vm = (t_corewar *)malloc(sizeof(t_corewar))))
		termination_with_perror("Error", ENOMEM);
	while (--n > -1)
		vm->cores[n] = NULL;
	vm->line_of_players = NULL;
	vm->number_of_players = 0;
	if (!(vm->start_carriage = (t_carriage*)malloc(sizeof(t_carriage))))
		termination_with_perror("Error", ENOMEM);
	return(vm);
}
