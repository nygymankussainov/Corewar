/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:41:56 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/04 18:56:59 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	op_xor(t_corewar *vm, t_carriage *carriage,
							uint8_t *arg_code)
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
	carriage->registers[reg] = arg1 ^ arg2;
	carriage->carry = (carriage->registers[reg] == 0) ? true : false;
}

void	op_zjmp(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int16_t		distance;

	distance = return_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE,
							carriage->operation->t_dir_size);
	if (carriage->carry)
		carriage->position = get_position(carriage->position, distance, true);
	else
		pass_args_bits(vm, carriage, arg_code);
}

void	op_fork(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int16_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE,
							carriage->operation->t_dir_size);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = get_position(carriage->position, distance, true);
	if (vm->visual && vm->sdl->sound)
		Mix_PlayChannel(-1, vm->sdl->copy_car, 0);
}

void	op_lfork(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	int16_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, (carriage->position + 1) % MEM_SIZE,
							carriage->operation->t_dir_size);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = get_position(carriage->position, distance, false);
	if (vm->visual && vm->sdl->sound)
		Mix_PlayChannel(-1, vm->sdl->copy_car, 0);
}

void	op_aff(t_corewar *vm, t_carriage *carriage, uint8_t *arg_code)
{
	char	output;
	uint8_t	reg_nbr;

	reg_nbr = vm->arena[(carriage->position + 2) % MEM_SIZE].value;
	output = carriage->registers[reg_nbr];
	if (vm->flag_a)
		ft_putchar(output);
}
