/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:36:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/30 17:07:40 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# define OP_NUMBER	16

# include "op.h"
# include <stdbool.h>
# include <sys/types.h>

typedef struct	s_ops
{
	char		*name;
	u_int8_t	opcode;
	int			args_number;
	int			args_type[3];
	bool		affect_carry;
	int			args_type_code;
	int			t_dir_size;
	int			cycles;
	int			(*f)(t_major *, t_carr *, t_player *);
}				t_ops;

static t_ops	g_ops[OP_NUMBER] = {
	{
		.name = "live",
		.opcode = 0x01,
		.args_number = 1,
		.args_type = {T_DIR, 0, 0},
		.affect_carry = 0,
		.args_type_code = 0,
		.t_dir_size = DIR_SIZE,
		.cycles = 10,
		.f = live
	},
	{
		.name = "ld",
		.opcode = 0x02,
		.args_number = 2,
		.args_type = {T_DIR | T_IND, T_REG, 0},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 5,
		.f = ld
	},
	{
		.name = "st",
		.opcode = 0x03,
		.args_number = 2,
		.args_type = {T_REG, T_REG | T_IND, 0},
		.affect_carry = 0,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 5
	},
	{
		.name = "add",
		.opcode = 0x04,
		.args_number = 3,
		.args_type = {T_REG, T_REG, T_REG},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 10
	},
	{
		.name = "sub",
		.opcode = 0x05,
		.args_number = 3,
		.args_type = {T_REG, T_REG, T_REG},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 10
	},
	{
		.name = "and",
		.opcode = 0x06,
		.args_number = 3,
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 6
	},
	{
		.name = "or",
		.opcode = 0x07,
		.args_number = 3,
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 6
	},
	{
		.name = "xor",
		.opcode = 0x08,
		.args_number = 3,
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 6
	},
	{
		.name = "zjmp",
		.opcode = 0x09,
		.args_number = 1,
		.args_type = {T_DIR, 0, 0},
		.affect_carry = 0,
		.args_type_code = 0,
		.t_dir_size = IND_SIZE,
		.cycles = 20
	},
	{
		.name = "ldi",
		.opcode = 0x0a,
		.args_number = 3,
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.affect_carry = 0,
		.args_type_code = 1,
		.t_dir_size = IND_SIZE,
		.cycles = 25
	},
	{
		.name = "sti",
		.opcode = 0x0b,
		.args_number = 3,
		.args_type = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.affect_carry = 0,
		.args_type_code = 1,
		.t_dir_size = IND_SIZE,
		.cycles = 25
	},
	{
		.name = "fork",
		.opcode = 0x0c,
		.args_number = 1,
		.args_type = {T_DIR, 0, 0},
		.affect_carry = 0,
		.args_type_code = 0,
		.t_dir_size = IND_SIZE,
		.cycles = 800
	},
	{
		.name = "lld",
		.opcode = 0x0d,
		.args_number = 2,
		.args_type = {T_DIR | T_IND, T_REG, 0},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 10
	},
	{
		.name = "lldi",
		.opcode = 0x0e,
		.args_number = 3,
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.affect_carry = 1,
		.args_type_code = 1,
		.t_dir_size = IND_SIZE,
		.cycles = 50
	},
	{
		.name = "lfork",
		.opcode = 0x0f,
		.args_number = 1,
		.args_type = {T_DIR, 0, 0},
		.affect_carry = 0,
		.args_type_code = 0,
		.t_dir_size = IND_SIZE,
		.cycles = 1000
	},
	{
		.name = "aff",
		.opcode = 0x10,
		.args_number = 1,
		.args_type = {T_REG, 0, 0},
		.affect_carry = 0,
		.args_type_code = 1,
		.t_dir_size = DIR_SIZE,
		.cycles = 2
	}
};

#endif
