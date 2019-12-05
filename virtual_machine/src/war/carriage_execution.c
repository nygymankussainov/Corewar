/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:37:50 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/05 19:01:12 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			set_carriage_op(t_corewar *vm, t_carriage *carriage)
{
	if (vm->arena[carriage->position].value > 0
			&& vm->arena[carriage->position].value < 17)
	{
		carriage->operation =
						&g_op_array[vm->arena[carriage->position].value - 1];
		carriage->cycles_before_operation =
									carriage->operation->cycles_to_execution;
	}
	else
	{
		carriage->operation = NULL;
		carriage->cycles_before_operation = 0;
	}
}

void			execute_carriage_op(t_corewar *vm, t_carriage *carriage)
{
	uint8_t		*arg_code;
	uint8_t		i;

	i = 0;
	arg_code = vm->arg_code;
	while (i < 4)
		arg_code[i++] = 0;
	if (carriage->operation != NULL)
	{
		set_arg_code(vm, carriage, &arg_code);
		if (is_valid_format(vm, carriage, arg_code))
			carriage->operation->func(vm, carriage, arg_code);
		if (carriage->operation->code != 0x09)
			pass_args_bits(carriage, arg_code);
	}
}

void			execute_carriages(t_corewar **vm)
{
	t_carriage	*carriage;

	(*vm)->current_cycles++;
	carriage = (*vm)->start_carriage;
	while (carriage)
	{
		if ((*vm)->visual == true)
		{
			vis_corewar(*vm);
			handle_key_press(*vm, NULL, false);
		}
		if (carriage->cycles_before_operation == 0)
			set_carriage_op((*vm), carriage);
		if (carriage->cycles_before_operation > 0)
			carriage->cycles_before_operation--;
		if (carriage->cycles_before_operation == 0
					&& carriage->operation != NULL)
			execute_carriage_op(*vm, carriage);
		else if (carriage->cycles_before_operation == 0)
			carriage->position = (carriage->position + 1) % MEM_SIZE;
		carriage = carriage->next;
	}
}
