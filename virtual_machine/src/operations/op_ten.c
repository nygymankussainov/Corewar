/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ten.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:41:20 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/05 14:36:50 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			op_lldi(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		arg3;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0],
						carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1],
						carriage->operation->t_dir_size);
	arg3 = return_arg(vm->arena, &position, arg_code[2],
						carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena,
				get_position(carriage->position, arg1, true), 4);
	else if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[arg3] = return_bytes(vm->arena,
		get_position(carriage->position,
						(int64_t)arg1 + (int64_t)arg2, false), 4);
	carriage->carry = (arg1 == 0) ? true : false;
}

void			op_add(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int8_t		reg1;
	int8_t		reg2;
	int8_t		res_reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	reg1 = return_arg(vm->arena, &position, arg_code[0],
						carriage->operation->t_dir_size);
	reg2 = return_arg(vm->arena, &position, arg_code[1],
						carriage->operation->t_dir_size);
	res_reg = return_arg(vm->arena, &position, arg_code[2],
						carriage->operation->t_dir_size);
	carriage->registers[res_reg] =
						carriage->registers[reg1] + carriage->registers[reg2];
	carriage->carry = (carriage->registers[res_reg] == 0) ? true : false;
}

void			op_sub(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	uint8_t		reg1;
	uint8_t		reg2;
	uint8_t		res_reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	reg1 = return_arg(vm->arena, &position, arg_code[0],
						carriage->operation->t_dir_size);
	reg2 = return_arg(vm->arena, &position, arg_code[1],
						carriage->operation->t_dir_size);
	res_reg = return_arg(vm->arena, &position, arg_code[2],
						carriage->operation->t_dir_size);
	carriage->registers[res_reg] =
						carriage->registers[reg1] - carriage->registers[reg2];
	carriage->carry = (carriage->registers[res_reg] == 0) ? true : false;
}

void			op_and(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0],
						carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1],
						carriage->operation->t_dir_size);
	reg = return_arg(vm->arena, &position, arg_code[2],
						carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena,
				get_position(carriage->position, arg1, true), 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena,
				get_position(carriage->position, arg2, true), 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 & arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void			op_or(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0],
						carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1],
						carriage->operation->t_dir_size);
	reg = return_arg(vm->arena, &position, arg_code[2],
						carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena,
						get_position(carriage->position, arg1, true), 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena,
						get_position(carriage->position, arg2, true), 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 | arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}
