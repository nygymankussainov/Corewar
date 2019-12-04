/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_five.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:40:16 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/04 18:40:59 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

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
