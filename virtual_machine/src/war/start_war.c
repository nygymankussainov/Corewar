/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/12 15:08:51 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				carriage_actions(t_corewar *vm)
{
	t_carriage		*tmp;
	uint8_t			byte_with_command;
	t_operation		op;

	tmp = vm->start_carriage;
	while (tmp) //пока не кончатся каретки считываю их команды
	{
		if (tmp->cycles_before_operation == 0)
		{
			if (tmp->operation != 0)
			{
				//выполнить операцию
				op = op_array[tmp->operation - 1];
				op_array[tmp->operation - 1].func(vm, tmp);
				tmp->operation = 0;
				tmp->cycles_before_operation = 0;
				//если после выполнения операции в каретку сразу нужно записать новую - изменить следующее условие
				//(убрать/модифицировать esle)
			}
			else
			{
				// записать в каретку новую операцию
				byte_with_command = vm->arena[tmp->position];
				if (byte_with_command >= 1 && byte_with_command <= 11)
				{
					tmp->operation = byte_with_command;
					tmp->cycles_before_operation = op_array[byte_with_command - 1].cycles_to_execution;
				}
				else
					tmp->position++; //Если же код операции ошибочен, необходимо просто переместить каретку на следующий байт.
			}
		}
		else
			tmp->cycles_before_operation--;
		tmp = tmp->next;
	}
}

void				start_war(t_corewar *vm)
{
	while (1)
	{
		if (vm->cycles_to_die <= 0) //или нет кареток
		{
			//удалять все каретки и печатать имя победителя?
			// exit
		}
		else if (vm->total_cycles == vm->cycles_to_die)
		{
			vm->check_count++;
			//ПРОВЕРКА ВСЕХ КАРЕТОК
			// Мертвой считается каретка, которая выполняла операцию live cycles_to_die циклов назад или более
			if (vm->live_count >= NBR_LIVE)
				vm->cycles_to_die -= CYCLE_DELTA;
			vm->total_cycles = 0;
			vm->live_count = 0;
		}
		else if (vm->check_count >= MAX_CHECKS)
		{
			vm->cycles_to_die -= CYCLE_DELTA;
		}
		else
		{
			carriage_actions(vm);
		}
		vm->total_cycles++;
	}
}


/*
T_REG 01
T_DIR 10
T_IND 11

op_live
op_ld
op_st
op_add
op_sub
op_and
op_or
op_xor
op_zjmp
op_ldi
op_sti
op_fork
op_lld
op_lldi
op_lfork
op_aff

*/