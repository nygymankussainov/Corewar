/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:44:29 by egiant            #+#    #+#             */
/*   Updated: 2019/11/17 12:21:42 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			set_carriages(t_corewar *vm, uint16_t position_step)
{
	short		i;
	short		n;
	t_carriage	*cur_carriage;
	t_carriage	*new_carriage;

	n = 0;
	i = vm->number_of_players;
	vm->start_carriage = init_carriage(vm, vm->cores[n]);
	cur_carriage = vm->start_carriage;
	while (i-- > 0)
	{
		cur_carriage->id = n + 1;
		cur_carriage->position = (cur_carriage->next)
			? cur_carriage->next->id * position_step : 0;
		cur_carriage->adress = (cur_carriage->next)
					? &(vm->arena[cur_carriage->next->id * position_step].value) : &(vm->arena[0].value);
		if (i != 0)
		{
			new_carriage = init_carriage(vm, vm->cores[++n]);
			new_carriage->next = cur_carriage;
			cur_carriage = new_carriage;
		}
	}
	vm->start_carriage = new_carriage; // т.к первой стоит каретка последнего игрока */
} //если писать vm->start_carriage = cur_carriage не работает (не отображается next)

void		set_exec_code(t_point *arena, uint16_t position, t_core *core)
{
	uint16_t	i;

	i = 0;
	while (i < CHAMP_MAX_SIZE) //(i < core->exec_code_size) ??? р-р 16, но код займет 22 байта (8 нулевых)
	{
		arena[position + i].value = core->exec_code[i];
		arena[position + i].color = core->color;
		i++;
	}
}