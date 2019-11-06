/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:08 by egiant            #+#    #+#             */
/*   Updated: 2019/11/06 15:43:02 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

t_carriage		*init_carriage(t_corewar *vm, t_core *player)
{
	short		n;
	t_carriage	*carriage;
	
	n = 15;
	if (!(carriage = (t_carriage*)malloc(sizeof(t_carriage))))
		termination_with_perror("Error", ENOMEM);
	carriage->id = (vm->start_carriage) ? vm->start_carriage->id + 1 : 0;
	carriage->carry = false;
	carriage->operation = 0;
	carriage->position = 0;
	carriage->cycle_was_live = 0; //цикл, в котором в последний раз была выполнена операция live
	carriage->cycles_before_operation = 0; //количество циклов, оставшиеся до исполнения операции, на которой стоит каретка
	carriage->offset_next_operation = 0; // количество байт, которые нужно будет «перешагнуть», чтобы оказаться на следующей операции
	carriage->next = NULL;
	while (n != 0)
		carriage->registers[n--] = 0;
	carriage->registers[0] = -((int)(player->id));
	carriage->player = player;
	return (carriage);
}

void			init_arena(t_corewar *vm)
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
	set_carriages(vm, position_step);
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
	vm->start_carriage = NULL;
	vm->winner_id = 0;
	vm->total_cycles = 0;
	vm->current_cycles = 0;
	vm->cycles_to_die = 0;
	vm->check_count = 0;
	return(vm);
}
