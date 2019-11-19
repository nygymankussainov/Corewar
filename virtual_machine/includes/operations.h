/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:17:43 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/19 15:43:25 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

#include "virtual_machine.h"

typedef struct s_corewar		t_corewar;
typedef struct s_carriage		t_carriage;

typedef struct		s_operation
{
	char			*name;
	uint8_t			code;
	uint8_t			number_of_arguments;
	bool			args_types_code;
	uint8_t			args_types[3];
	uint8_t			changes_carry; //1 или 0
	uint8_t			t_dir_size;
	uint16_t		cycles_to_execution;
	void			(*func)(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
}					t_operation;

void				op_live(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_ld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_st(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_add(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_sub(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_and(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_or(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_xor(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_zjmp(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_ldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_sti(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_fork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_lld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_lldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_lfork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);
void				op_aff(t_corewar *vm, t_carriage *carriage, int8_t *arg_code);

static uint8_t			type_sizes[3] = {1, 4, 2};

static t_operation		op_array[16] = {
	{
		.name = "live",
		.code = 0x01,
		.number_of_arguments = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.changes_carry = false,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_live
	},
	{
		.name = "ld",
		.code = 0x02,
		.number_of_arguments = 2,
		.args_types_code = true,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 5,
		.func = &op_ld
	},
	{
		.name = "st",
		.code = 0x03,
		.number_of_arguments = 2,
		.args_types_code = true,
		.args_types = {T_REG, T_REG | T_IND, 0},
		.changes_carry = false,
		.t_dir_size = 4,
		.cycles_to_execution = 5,
		.func = &op_st
	},
	{
		.name = "add",
		.code = 0x04,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG, T_REG},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_add
	},
	{
		.name = "sub",
		.code = 0x05,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG, T_REG},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_sub
	},
	{
		.name = "and",
		.code = 0x06,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 6,
		.func = &op_and
	},
	{
		.name = "or",
		.code = 0x07,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 6,
		.func = &op_or
	},
	{
		.name = "xor",
		.code = 0x08,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 6,
		.func = &op_xor
	},
	{
		.name = "zjmp",
		.code = 0x09,
		.number_of_arguments = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.changes_carry = false,
		.t_dir_size = 2,
		.cycles_to_execution = 20,
		.func = &op_zjmp
	},
	{
		.name = "ldi",
		.code = 0x0a,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.changes_carry = false,
		.t_dir_size = 2,
		.cycles_to_execution = 25,
		.func = &op_ldi
	},
	{
		.name = "sti",
		.code = 0x0b,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.changes_carry = false,
		.t_dir_size = 2,
		.cycles_to_execution = 25,
		.func = &op_sti
	},
	{
		.name = "fork",
		.code = 0x0c,
		.number_of_arguments = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.changes_carry = false,
		.t_dir_size = 2,
		.cycles_to_execution = 800,
		.func = &op_fork
	},
	{
		.name = "lld",
		.code = 0x0d,
		.number_of_arguments = 2,
		.args_types_code = true,
		.args_types = {T_DIR | T_IND, T_REG, 0},
		.changes_carry = true,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_lld
	},
	{
		.name = "lldi",
		.code = 0x0e,
		.number_of_arguments = 3,
		.args_types_code = true,
		.args_types = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.changes_carry = true,
		.t_dir_size = 2,
		.cycles_to_execution = 50,
		.func = &op_lldi
	},
	{
		.name = "lfork",
		.code = 0x0f,
		.number_of_arguments = 1,
		.args_types_code = false,
		.args_types = {T_DIR, 0, 0},
		.changes_carry = false,
		.t_dir_size = 2,
		.cycles_to_execution = 1000,
		.func = &op_lfork
	},
	{
		.name = "aff",
		.code = 0x10,
		.number_of_arguments = 1,
		.args_types_code = true,
		.args_types = {T_REG, 0, 0},
		.changes_carry = false,
		.t_dir_size = 4,
		.cycles_to_execution = 2,
		.func = &op_aff
	}
};
#endif
