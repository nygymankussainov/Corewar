/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/09 14:02:53 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void				do_op(t_corewar *vm, t_carriage *carriage, t_operation op)
{
	static uint8_t	args[3];
	uint8_t			*args_byte_code;

	args_byte_code = carriage->adress + 1;
	// printf("%hhu\n", *args_byte_code);
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
        ft_printf("%d\n", tmp->position);
		byte_with_command = &tmp->position;
		if (*byte_with_command >= 1 && *byte_with_command <= 11)
		{
			op = op_array[*byte_with_command - 1];
			do_op(vm, tmp, op);
		}
		tmp = tmp->next;
	}
}
