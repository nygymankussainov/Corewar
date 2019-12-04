/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:37:50 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/04 16:13:00 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
** why necessary remember value of invalid operation?
*/
void	set_carriage_op(t_corewar *vm, t_carriage *carriage)
{
	if (vm->arena[carriage->position].value > 0 && vm->arena[carriage->position].value < 17)
	{
		carriage->operation = &op_array[vm->arena[carriage->position].value - 1];
		carriage->cycles_before_operation = carriage->operation->cycles_to_execution;
	}
	else
	{
		carriage->operation = NULL;
		carriage->cycles_before_operation = 0;
	}
}

void	execute_carriage_op(t_corewar *vm, t_carriage *carriage)
{
	uint8_t	*arg_code;
	uint8_t	i;
	
	if (!(arg_code = (uint8_t*)malloc(sizeof(uint8_t) * 4)))
		termination_with_perror("Error", ENOMEM);
	i = 0;
	// while (i < 4)
	// {
	// 	arg_code[i] = 0;
	// 	i++;
	// }
	if (carriage->operation != NULL)
	{
		set_arg_code(vm, carriage, &arg_code);
		if (is_valid_format(vm, carriage, arg_code))
		{
			carriage->operation->func(vm, carriage, arg_code);
		}
		if (carriage->operation->code != 0x09)
			pass_args_bits(vm, carriage, arg_code);
	}
	if (arg_code)
		free(arg_code);
}

void    execute_carriages(t_corewar **vm)
{
	t_carriage	*carriage;

    //while ((*vm)->current_cycles != (*vm)->cycles_to_die && (*vm)->cycles_to_die > 0)
	//{
		(*vm)->current_cycles++;
		carriage = (*vm)->start_carriage;
		if ((*vm)->current_cycles + (*vm)->total_cycles == 18115)
		 	ft_printf("");
		while (carriage)
		{
			if (carriage->cycles_before_operation == 0)
				set_carriage_op((*vm), carriage);
			if (carriage->cycles_before_operation > 0)
				carriage->cycles_before_operation--;
			if (carriage->cycles_before_operation == 0 && carriage->operation != NULL)
				execute_carriage_op(*vm, carriage);
			else if (carriage->cycles_before_operation == 0)
				carriage->position = (carriage->position + 1) % MEM_SIZE;
			if (carriage->cycles_before_operation == 0 && (*vm)->visual == true)
			{
				vis_corewar(*vm);
				handle_key_press(*vm, NULL, false);
			}
			carriage = carriage->next;
		}
		// if ((*vm)->dumps != (*vm)->cycles_to_die && (*vm)->dumps == (*vm)->current_cycles + (*vm)->total_cycles)
		// {
		// 	display_array((*vm)->arena, 64, 64);
		// 	exit (0);
		// }
	//}
}
