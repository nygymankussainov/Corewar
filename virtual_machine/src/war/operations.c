/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:06:18 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/13 16:37:46 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

/*
T_REG 01
T_DIR 10
T_IND 11
live, add, sub, zjmp, fork, lfork, aff
*/

int32_t				return_bytes(uint8_t *arena, uint16_t position, uint8_t bytes_nbr)
{
	int32_t		res;

	res = 0;
	if (bytes_nbr == 1)
		res = arena[position % MEM_SIZE];
	else if (bytes_nbr == 2)
		res = arena[position % MEM_SIZE] << 8 |
				arena[(position + 1) % MEM_SIZE];
	else if	(bytes_nbr == 4)
		res = arena[position % MEM_SIZE] << 24 |
			arena[(position + 1) % MEM_SIZE] << 16 |
			arena[(position + 2) % MEM_SIZE] << 8 |
			arena[(position + 3) % MEM_SIZE];
	else
		ft_printf("Wrong bytes_nbr");
	return(res);
}

void				op_live(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	t_core	*core;
	uint8_t	player_code;

	vm->live_count++;
    carriage->cycle_was_live = vm->total_cycles + vm->current_cycles;
	player_code = 256 - arg_code[0];
    if (player_code > 0 && player_code <= MAX_PLAYERS)
    {
		core = vm->cores[player_code];
		core->cycle_was_live = vm->total_cycles + vm->current_cycles;
		vm->winner = core;
	}
}

void				op_ld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_st(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_add(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int8_t	reg1;
	int8_t	reg2;
	int8_t	res_reg;

	reg1 = return_bytes(vm->arena, carriage->position + 2, T_REG);
	reg2 = return_bytes(vm->arena, carriage->position + 3, T_REG);
	res_reg = return_bytes(vm->arena, carriage->position + 4, T_REG);
	carriage->registers[res_reg] = carriage->registers[reg1] + carriage->registers[reg2];
	if (carriage->registers[res_reg] == 0)
		carriage->carry = 1;
	else
		carriage->carry = 0;
}

void				op_sub(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int8_t	reg1;
	int8_t	reg2;
	int8_t	res_reg;

	reg1 = return_bytes(vm->arena, carriage->position + 2, T_REG);
	reg2 = return_bytes(vm->arena, carriage->position + 3, T_REG);
	res_reg = return_bytes(vm->arena, carriage->position + 4, T_REG);
	carriage->registers[res_reg] = carriage->registers[reg1] - carriage->registers[reg2];
	if (carriage->registers[res_reg] == 0)
		carriage->carry = 1;
	else
		carriage->carry = 0;
}

void				op_and(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		arg1;
	int32_t		arg2;

	if (arg_code[0])
		arg1 = return_bytes(vm->arena, carriage->position + 2, T_REG);
}

void				op_or(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_xor(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_zjmp(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		distance;

	distance = return_bytes(vm->arena, carriage->position + 1, T_DIR);
	if (carriage->carry)
		carriage->position = (carriage->position + distance % IDX_MOD) % MEM_SIZE;
}

void				op_ldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_sti(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_fork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, carriage->position + 1, T_DIR);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = (new_carriage->position + distance % IDX_MOD) % MEM_SIZE;
}

void				op_lld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_lldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_lfork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		distance;
	t_carriage	*new_carriage;

	distance = return_bytes(vm->arena, carriage->position + 1, T_DIR);
	new_carriage = copy_carriage(vm, carriage);
	new_carriage->position = (new_carriage->position + distance) % MEM_SIZE;
}

void				op_aff(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	char	output;
	uint8_t	reg_nbr;

	reg_nbr = vm->arena[(carriage->position + 2) % MEM_SIZE];
	output = carriage->registers[reg_nbr];
	ft_putchar(output);
}