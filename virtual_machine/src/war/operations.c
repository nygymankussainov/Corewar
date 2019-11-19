/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:57:01 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/19 21:06:03 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
T_REG 01
T_DIR 10
T_IND 11
live, add, sub, zjmp, fork, lfork, aff
*/

int32_t				return_bytes(t_point *arena, uint16_t position, uint8_t bytes_nbr)
{
	int32_t			res;

	res = 0;
	if (bytes_nbr == 1)
		res = arena[position % MEM_SIZE].value;
	else if (bytes_nbr == 2)
		res = arena[position % MEM_SIZE].value << 8 |
				arena[(position + 1) % MEM_SIZE].value;
	else if	(bytes_nbr == 4)
		res = arena[position % MEM_SIZE].value << 24 |
			arena[(position + 1) % MEM_SIZE].value << 16 |
			arena[(position + 2) % MEM_SIZE].value << 8 |
			arena[(position + 3) % MEM_SIZE].value;
	else
		ft_printf("Wrong bytes_nbr");
	return(res);
}

int32_t				return_arg(t_point *arena, uint16_t *position,
								int8_t arg_code, uint8_t t_dir_size)
{
	int8_t		reg;
	int16_t		ind;
	int16_t		dir16;
	int32_t		dir32;
	
	if (arg_code == 1)
	{
		reg = return_bytes(arena, *position, 1) - 1;
		*position += 1 % MEM_SIZE;
		return (reg);
	}
	else if (arg_code == 3)
	{
		ind = return_bytes(arena, *position, 2);
		*position += 2 % MEM_SIZE;
		return (ind);
	}
	else if (t_dir_size == 2)
	{
		dir16 = return_bytes(arena, *position, 2);
		*position += 2 % MEM_SIZE;
		return (dir16);
	}
	else
	{
		dir32 = return_bytes(arena, *position, 4);
		*position += 4 % MEM_SIZE;
		return (dir32);
	}
}

void				add_to_arena(t_point *arena, uint16_t position, int32_t code, t_carriage *carriage) // was uint32_t code
{
	// if (position == 2075)
	// 	ft_putstr("helo");
	arena[position].value = code >> 24;
	arena[position + 1].value = code >> 16 & 0x00FF;
	arena[position + 2].value = code >> 8 & 0x0000FF;
	arena[position + 3].value = code & 0x000000FF;
	arena[position].color = carriage->color;
	arena[position + 1].color = carriage->color;
	arena[position + 2].color = carriage->color;
	arena[position + 3].color = carriage->color;
	carriage->last_operation[0] = position;
	carriage->last_operation[1] = position + 1;
	carriage->last_operation[2] = position + 2;
	carriage->last_operation[3] = position + 3;
}

void				op_live(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	t_core			*core;
	int32_t			player_code;

	vm->live_count++;
    carriage->cycle_was_live = vm->total_cycles + vm->current_cycles;
	player_code = -return_bytes(vm->arena, carriage->position + 1, carriage->operation->t_dir_size);
	if (player_code > 0 && player_code <= vm->number_of_players)
    {
		vm->winner = vm->cores[player_code - 1]; //player_code - 1 т.к. обращаемся к массиву, который начинается с 0 индекса
		vm->winner->cycle_was_live = vm->total_cycles + vm->current_cycles;
		// ft_printf("Player %d (%s) is said to be alive\n", vm->winner->id, vm->winner->name);
	}
}

void				op_st(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t		arg1;
	int16_t		arg2;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	if (arg_code[1] == 1)
		carriage->registers[arg2] = carriage->registers[arg1];
	else
		add_to_arena(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE,
		carriage->registers[arg1], carriage);
}

void				op_sti(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t		arg1;
	int32_t		arg2;
	int32_t		arg3;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	arg3 = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	add_to_arena(vm->arena, (carriage->position + (arg2 + arg3) % IDX_MOD) % MEM_SIZE,
		carriage->registers[arg1], carriage);
}

void				op_ld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		arg1;
	uint8_t		arg2;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	carriage->registers[arg2] = arg1;
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_lld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		arg1;
	uint8_t		arg2;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1) % MEM_SIZE, 4);
	carriage->registers[arg2] = arg1;
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_ldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
    int32_t		arg1;
	int32_t		arg2;
	uint8_t		arg3;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	arg3 = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	else if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[arg3] = return_bytes(vm->arena,
		(carriage->position + ((int64_t)arg1 + (int64_t)arg2) % IDX_MOD) % MEM_SIZE, 4); // is it necessary? (int64_t)
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_lldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
    int32_t		arg1;
	int32_t		arg2;
	uint8_t		arg3;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	arg3 = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	else if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[arg3] = return_bytes(vm->arena,
		(carriage->position + (int64_t)arg1 + (int64_t)arg2) % MEM_SIZE, 4); // is it necessary? (int64_t)
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_add(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int8_t		reg1;
	int8_t		reg2;
	int8_t		res_reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	reg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	reg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	res_reg = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	carriage->registers[res_reg] = carriage->registers[reg1] + carriage->registers[reg2];
	carriage->carry = (carriage->registers[res_reg] == 0) ? true : false;
}

void				op_sub(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t		reg1;
	uint8_t		reg2;
	uint8_t		res_reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	reg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	reg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	res_reg = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	carriage->registers[res_reg] = carriage->registers[reg1] - carriage->registers[reg2];
	carriage->carry = (carriage->registers[res_reg] == 0) ? true : false;
}

void				op_and(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	reg = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 & arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void				op_or(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	reg = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 | arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void				op_xor(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	reg = return_arg(vm->arena, &position, arg_code[2], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 ^ arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void				op_zjmp(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int16_t 		distance;

	distance = return_bytes(vm->arena, carriage->position + 1, carriage->operation->t_dir_size);
	if (carriage->carry)
		carriage->position = (carriage->position + distance % IDX_MOD) % MEM_SIZE;
	else
		pass_args_bits(vm, carriage, arg_code);
}

void				op_fork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, carriage->position + 1, carriage->operation->t_dir_size);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = distance % IDX_MOD;
}

void				op_lfork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, carriage->position + 1, carriage->operation->t_dir_size);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = (new_carriage->position + distance) % MEM_SIZE;
}

void				op_aff(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	char	output;
	uint8_t	reg_nbr;

	reg_nbr = vm->arena[(carriage->position + 2) % MEM_SIZE].value;
	output = carriage->registers[reg_nbr];
	ft_putchar(output);
}
