/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/06 16:56:16 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				do_op(t_corewar *vm, t_carriage *carriage, t_operation op)
{
	static uint8_t	args[3];
	uint8_t			*args_byte_code;

	args_byte_code = carriage->adress + 1;
	printf("%hhu\n", *args_byte_code);
	//перейти на следующий байт в памяти
	//считать код аргументов, записать их в args /пример: 68 - 01 10 10 00
	//зная сколько байт занимает значение каждого аргумента получить значения и выполнить операцию
	

}

void				start_war(t_corewar *vm)
{
	t_carriage		*tmp;
	uint8_t			*byte_with_command;
	t_operation		op;

	tmp = vm->start_carriage;
	while (tmp) //пока не кончатся каретки? считываю их команды
	{
		byte_with_command = &tmp->position;
		if (*byte_with_command >= 1 && *byte_with_command <= 11)
		{
			op = op_array[*byte_with_command - 1];
			do_op(vm, tmp, op);
		}
		tmp = tmp->next;
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