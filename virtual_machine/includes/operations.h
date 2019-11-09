#ifndef OPERATIONS_H
# define OPERATIONS_H

#include "virtual_machine.h"

typedef struct s_corewar		t_corewar;

typedef struct		s_operation
{
	char			*name;
	uint8_t			code;
	uint8_t			number_of_arguments;
	uint8_t			changes_carry; //1 или 0
	uint8_t			t_dir_size;
	uint16_t		cycles_to_execution;
	void			(*func)(t_corewar *);
}					t_operation;

void				op_live(t_corewar *);
void				op_ld(t_corewar *);
void				op_st(t_corewar *);
void				op_add(t_corewar *);
void				op_sub(t_corewar *);
void				op_and(t_corewar *);
void				op_or(t_corewar *);
void				op_xor(t_corewar *);
void				op_zjmp(t_corewar *);
void				op_ldi(t_corewar *);
void				op_sti(t_corewar *);
void				op_fork(t_corewar *);
void				op_lld(t_corewar *);
void				op_lldi(t_corewar *);
void				op_lfork(t_corewar *);
void				op_aff(t_corewar *);


static t_operation	op_array[16] = {
	{
		.name = "live",
		.code = 0x01,
		.number_of_arguments = 1,
		.changes_carry = 0,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_live
	},

	{
		.name = "load",
		.code = 0x02,
		.number_of_arguments = 2,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 5,
		.func = &op_ld
	},

	{
		.name = "store",
		.code = 0x03,
		.number_of_arguments = 2,
		.changes_carry = 0,
		.t_dir_size = 4,
		.cycles_to_execution = 5,
		.func = &op_st
	},

	{
		.name = "addition",
		.code = 0x04,
		.number_of_arguments = 3,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_add
	},

	{
		.name = "subtraction",
		.code = 0x05,
		.number_of_arguments = 3,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_sub
	},

	{
		.name = "and",
		.code = 0x06,
		.number_of_arguments = 3,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 6,
		.func = &op_and
	},

	{
		.name = "or",
		.code = 0x07,
		.number_of_arguments = 3,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 6,
		.func = &op_or
	},

	{
		.name = "xor",
		.code = 0x08,
		.number_of_arguments = 3,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 6,
		.func = &op_xor
	},

	{
		.name = "jump if non-zero",
		.code = 0x09,
		.number_of_arguments = 1,
		.changes_carry = 0,
		.t_dir_size = 2,
		.cycles_to_execution = 20,
		.func = &op_zjmp
	},

	{
		.name = "load index",
		.code = 0x0a,
		.number_of_arguments = 3,
		.changes_carry = 0,
		.t_dir_size = 2,
		.cycles_to_execution = 25,
		.func = &op_ldi
	},

	{
		.name = "store index",
		.code = 0x0b,
		.number_of_arguments = 3,
		.changes_carry = 0,
		.t_dir_size = 2,
		.cycles_to_execution = 25,
		.func = &op_sti
	},

	{
		.name = "fork",
		.code = 0x0c,
		.number_of_arguments = 1,
		.changes_carry = 0,
		.t_dir_size = 2,
		.cycles_to_execution = 800,
		.func = &op_fork
	},

	{
		.name = "long load",
		.code = 0x0d,
		.number_of_arguments = 2,
		.changes_carry = 1,
		.t_dir_size = 4,
		.cycles_to_execution = 10,
		.func = &op_lld
	},

	{
		.name = "long load index",
		.code = 0x0e,
		.number_of_arguments = 3,
		.changes_carry = 1,
		.t_dir_size = 2,
		.cycles_to_execution = 50,
		.func = &op_lldi
	},

	{
		.name = "long fork",
		.code = 0x0f,
		.number_of_arguments = 1,
		.changes_carry = 0,
		.t_dir_size = 2,
		.cycles_to_execution = 1000,
		.func = &op_lfork
	},

	{
		.name = "aff",
		.code = 0x10,
		.number_of_arguments = 1,
		.changes_carry = 0,
		.t_dir_size = 4,
		.cycles_to_execution = 2,
		.func = &op_aff
	}
};

#endif
