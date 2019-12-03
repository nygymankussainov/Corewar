/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:57:01 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/03 18:49:10 by egiant           ###   ########.fr       */
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
								uint8_t arg_code, uint8_t t_dir_size)
{
	int8_t		reg;
	int16_t		ind;
	int16_t		dir16;
	int32_t		dir32;
	
	if (arg_code == 1)
	{
		reg = return_bytes(arena, *position, 1) - 1;
		*position = (*position + 1) % MEM_SIZE;
		return (reg);
	}
	else if (arg_code == 3)
	{
		ind = return_bytes(arena, *position, 2);
		*position = (*position + 2) % MEM_SIZE;
		return (ind);
	}
	else if (t_dir_size == 2)
	{
		dir16 = return_bytes(arena, *position, 2);
		*position = (*position + 2) % MEM_SIZE;
		return (dir16);
	}
	else
	{
		dir32 = return_bytes(arena, *position, 4);
		*position = (*position + 4) % MEM_SIZE;
		return (dir32);
	}
}

uint16_t			get_position(uint16_t cur_pos, int64_t arg, bool idx) // check!
{
	int8_t	sign;
	int32_t	res;

	if (arg < 0)
	{
		arg = -arg;
		sign = -1;
	}
	else
		sign = 1;
	if (idx)
		res = cur_pos + sign * (arg % IDX_MOD);
	else
		res = cur_pos + sign * arg;
	if (res < 0)
	{
		res = -res;
		res = MEM_SIZE - (res % MEM_SIZE);
	}
	return (res % MEM_SIZE);
}

void				add_to_arena(t_corewar *vm, uint16_t position, int32_t code, t_carriage *carriage) // was uint32_t code
{
	vm->arena[position].value = code >> 24;
	vm->arena[(position + 1) % MEM_SIZE].value = code >> 16 & 0x00FF;
	vm->arena[(position + 2) % MEM_SIZE].value = code >> 8 & 0x0000FF;
	vm->arena[(position + 3) % MEM_SIZE].value = code & 0x000000FF;
	vm->arena[position].color = carriage->color;
	vm->arena[(position + 1) % MEM_SIZE].color = carriage->color;
	vm->arena[(position + 2) % MEM_SIZE].color = carriage->color;
	vm->arena[(position + 3) % MEM_SIZE].color = carriage->color;
	vm->arena[position].light_count = 51;
	vm->arena[(position + 1) % MEM_SIZE].light_count = 51;
	vm->arena[(position + 2) % MEM_SIZE].light_count = 51;
	vm->arena[(position + 3) % MEM_SIZE].light_count = 51;
	carriage->last_operation[0] = position;
	carriage->last_operation[1] = (position + 1) % MEM_SIZE;
	carriage->last_operation[2] = (position + 2) % MEM_SIZE;
	carriage->last_operation[3] = (position + 3) % MEM_SIZE;
}

void				op_live(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	t_core			*core;
	int32_t			player_code;

	vm->live_count++;
    carriage->cycle_was_live = vm->total_cycles + vm->current_cycles;
	player_code = -return_bytes(vm->arena, carriage->position + 1, carriage->operation->t_dir_size);
	vm->arena[carriage->position].live_count = 50;
	if (player_code > 0 && player_code <= vm->number_of_players)
    {
		vm->cores[player_code - 1]->cycle_was_live = vm->total_cycles + vm->current_cycles;
		vm->cores[player_code - 1]->lives_in_period++;
		vm->winner = vm->cores[player_code - 1];
		vm->winner->cycle_was_live = vm->total_cycles + vm->current_cycles;
	}
	if (vm->visual && vm->sdl->sound)
		Mix_PlayChannel(-1, vm->sdl->live, 0);
}

void				op_st(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		add_to_arena(vm, get_position(carriage->position, arg2, true),
		carriage->registers[arg1], carriage);
}

void				op_sti(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		arg2 = return_bytes(vm->arena, get_position(carriage->position, arg2, true), 4);
	else if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	if (arg_code[2] == 1)
		arg3 = carriage->registers[arg3];
	add_to_arena(vm, get_position(carriage->position, (int64_t)arg2 + (int64_t)arg3, true),
		carriage->registers[arg1], carriage);
}

void				op_ld(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int32_t		arg1;
	uint8_t		arg2;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, true), REG_SIZE);
	carriage->registers[arg2] = arg1;
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_lld(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int32_t		arg1;
	uint8_t		arg2;
	uint16_t	position;

	position = (carriage->position + 2) % MEM_SIZE;
	arg1 = return_arg(vm->arena, &position, arg_code[0], carriage->operation->t_dir_size);
	arg2 = return_arg(vm->arena, &position, arg_code[1], carriage->operation->t_dir_size);
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, false), REG_SIZE);
	carriage->registers[arg2] = arg1;
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_ldi(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, true), 4);
	else if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[arg3] = return_bytes(vm->arena,
	get_position(carriage->position, (int64_t)arg1 + (int64_t)arg2, true), REG_SIZE);
}

void				op_lldi(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, true), 4);
	else if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[arg3] = return_bytes(vm->arena,
		get_position(carriage->position, (int64_t)arg1 + (int64_t)arg2, false), 4);
	carriage->carry = (arg1 == 0) ? true : false;
}

void				op_add(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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

void				op_sub(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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

void				op_and(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, true), 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, get_position(carriage->position, arg2, true), 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 & arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void				op_or(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, true), 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, get_position(carriage->position, arg2, true), 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 | arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void				op_xor(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
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
		arg1 = return_bytes(vm->arena, get_position(carriage->position, arg1, true), 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, get_position(carriage->position, arg2, true), 4);
	if (arg_code[0] == 1)
		arg1 = carriage->registers[arg1];
	if (arg_code[1] == 1)
		arg2 = carriage->registers[arg2];
	carriage->registers[reg] = arg1 ^ arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void				op_zjmp(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int16_t 		distance;

	distance = return_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, carriage->operation->t_dir_size);
	if (carriage->carry)
		carriage->position = get_position(carriage->position, distance, true);
	else
		pass_args_bits(vm, carriage, arg_code);
}

void				op_fork(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int16_t		distance;
	t_carriage	*new_carriage;

 	distance = return_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, carriage->operation->t_dir_size);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = get_position(carriage->position, distance, true);
	if (vm->visual && vm->sdl->sound)
		Mix_PlayChannel(-1, vm->sdl->copy_car, 0);
}

void				op_lfork(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int16_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE, carriage->operation->t_dir_size);
	//if (vm->total_cycles + vm->current_cycles > 15900 && carriage->position + distance >= 960)
	//	printf("zj\n");
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = get_position(carriage->position, distance, false);
	if (vm->visual && vm->sdl->sound)
		Mix_PlayChannel(-1, vm->sdl->copy_car, 0);
}

void				op_aff(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	char	output;
	uint8_t	reg_nbr;

	reg_nbr = vm->arena[(carriage->position + 2) % MEM_SIZE].value; //почему в этой операции есть код аргумеетов если аргумент всегда один?
	output = carriage->registers[reg_nbr];
	if (vm->flag_a)
		ft_putchar(output);
}