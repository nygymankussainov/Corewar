/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:38:51 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/13 16:44:52 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

bool	is_valid_reg(t_corewar *vm, t_carriage *carriage,
					int8_t arg_code[4], uint8_t index)
{
	uint8_t		offset;
	uint8_t		i;

	offset = 2;
	i = 0;
	while (i < index)
	{
		if (arg_code[i] == 2)
			offset += carriage->operation->t_dir_size;
		else if (arg_code[i] == 3)
			offset += 2;
		i++;
	}
	if (vm->arena[(carriage->position + offset) % MEM_SIZE] < 1 ||
			vm->arena[(carriage->position + offset) % MEM_SIZE] > REG_NUMBER)
		return (false);
	else
		return (true);
}

void	set_arg_code(t_corewar *vm, t_carriage *carriage, int8_t **arg_code)
{
	uint8_t	i;

	if (carriage->operation->args_types_code)
	{
		i = 0;
		while (i < 4)
		{
			(*arg_code)[i] = vm->arena[(carriage->position + 1) % MEM_SIZE]
			<< (2 * i) >> 6 & 3;
			i++;
		}
	}
	else
	{
		free(*arg_code);
		*arg_code = NULL;
	}
}

bool	if_valid_format(t_corewar *vm, t_carriage *carriage,
						int8_t *arg_code, uint8_t i)
{
	if (i < carriage->operation->number_of_arguments && arg_code[i] == 1 &&
		is_valid_reg(vm, carriage, arg_code, i) == false &&
		(arg_code[i] & carriage->operation->args_types[i]) == false)
		return(false);
	else if (i < carriage->operation->number_of_arguments &&
		(arg_code[i] & carriage->operation->args_types[i]) == false)
		return (false);
	else if (i >= carriage->operation->number_of_arguments &&
        arg_code[i] != 0)
		return (false);
	return (true);
}

bool	is_valid_format(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t	i;
	
	if (carriage->operation->args_types_code)
	{
		i = 0;
		while (i < 4)
		{
			if (if_valid_format(vm, carriage, arg_code, i) == false)
				return (false);
			i++;
		}
	}
	return (true);
}

void	pass_args_bits(t_corewar *vm, t_carriage *carriage, int8_t arg_code[4])
{
	uint8_t	bytes_count;
	uint8_t	i;

	if (carriage->operation->args_types_code)
	{
		bytes_count = 2;
		i = 0;
		while (i < carriage->operation->number_of_arguments)
		{
			if (arg_code[i] == 1)
				bytes_count += 1;
			else if (arg_code[i] == 2)
				bytes_count += carriage->operation->t_dir_size;
			else if (arg_code[i] == 3)
				bytes_count += 2;
			i++;
		}
	}
	else
		bytes_count = 1 + carriage->operation->t_dir_size;
	carriage->position = (carriage->position + bytes_count) % MEM_SIZE;
}
