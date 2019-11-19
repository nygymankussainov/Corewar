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

void				add_to_arena(t_point *arena, uint16_t position, int32_t code, t_carriage *carriage) // was uint32_t code
{
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
	uint8_t			reg_num;
	uint16_t		arg1;
	uint16_t		pos;

	pos = (carriage->position + 2) % MEM_SIZE;
	reg_num = vm->arena[pos++].value;
	if (arg_code[1] == 1)
	{
		arg1 = vm->arena[pos % MEM_SIZE].value;
		carriage->registers[arg1] = carriage->registers[reg_num];
	}
	else
	{
		arg1 = vm->arena[pos % MEM_SIZE].value << 8 | vm->arena[(pos + 1) % MEM_SIZE].value; //T_IND
		add_to_arena(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE,
			carriage->registers[reg_num - 1], carriage);
	}
}

void				op_sti(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint16_t		arg1;
	uint16_t		arg2;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	reg_num = vm->arena[pos++].value;
	if (arg_code[1] == 1)
	{	
		arg1 = return_bytes(vm->arena, pos, T_REG); //T_REG считываю 1 байт
		++pos;
	}
	else if (arg_code[1] == 2)
	{
		arg1 = return_bytes(vm->arena, pos, T_DIR); // T_DIR считываю 2 байта
		pos += 2;
	}
	else
	{
		arg1 = return_bytes(vm->arena, pos, T_IND); //T_IND
		pos += 2;
		adress = carriage->position + (arg1 % IDX_MOD);
		arg1 = return_bytes(vm->arena, adress, carriage->operation->t_dir_size);
	}
	arg2 = (arg_code[2] == 1) ? return_bytes(vm->arena, pos, T_REG) : return_bytes(vm->arena, pos, T_DIR);
	add_to_arena(vm->arena, carriage->position + (arg1 + arg2) % IDX_MOD, carriage->registers[reg_num - 1], carriage);
}

void				op_ld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	int16_t			ind;
	int32_t			arg1;
	uint16_t		pos;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 2)
	{
		arg1 = return_bytes(vm->arena, pos, carriage->operation->t_dir_size);
		pos += 4;
	}
	else
	{
		ind = return_bytes(vm->arena, pos, 2);
		pos += 2;
		arg1 = return_bytes(vm->arena, (carriage->position + ind % IDX_MOD) % MEM_SIZE, 4);
	}
	reg_num = vm->arena[pos % MEM_SIZE].value;
	carriage->registers[reg_num - 1] = arg1;
	carriage->carry = (arg1 == 0) ? 1 : 0;
}

void				op_lld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	int16_t			ind;
	int32_t			arg1;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 2)
	{
		arg1 = return_bytes(vm->arena, pos, carriage->operation->t_dir_size);
		pos += 4;
	}
	else
	{
		ind = return_bytes(vm->arena, pos, 2);
		pos += 2;
		arg1 = return_bytes(vm->arena, (carriage->position + ind) % MEM_SIZE, 4);
		//Не применяя усечение по модулю
	}
	reg_num = vm->arena[pos % MEM_SIZE].value;
	carriage->registers[reg_num] = arg1;
}

void				op_ldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
    uint8_t			reg_num;
	uint32_t		arg1;
	uint16_t		arg2;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 1)
		arg1 = vm->arena[pos++].value;
	else
	{
		arg1 = return_bytes(vm->arena, pos, carriage->operation->t_dir_size);
		pos += 2;
		if (arg_code[0] == 3)
		{
			//сколько байт тут считывать 4 или 2??
			arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE,
			carriage->operation->t_dir_size);
		}
	}
	if (arg_code[1] == 1)
	{
		arg2 = return_bytes(vm->arena, pos, T_REG);
		++pos;
	}
	else
	{
		arg2 = return_bytes(vm->arena, pos, carriage->operation->t_dir_size);
		pos += 2;
	}
	reg_num = vm->arena[pos % MEM_SIZE].value;
	adress = (carriage->position + (arg1 + arg2) % IDX_MOD) % MEM_SIZE;
	carriage->registers[reg_num] = return_bytes(vm->arena, adress, REG_SIZE);
}

void				op_lldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint32_t		arg1;
	uint16_t		arg2;
	uint16_t		pos;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 1)
		arg1 = vm->arena[pos++].value;
	else
	{
		arg1 = return_bytes(vm->arena, pos, carriage->operation->t_dir_size);
		pos += 2;
		if (arg_code[0] == 3)
		{
			//когда t_ind arg_code[0] = 3??
			arg1 = return_bytes(vm->arena, carriage->position + arg1, carriage->operation->t_dir_size);
		}
	}
	if (arg_code[1] == 1)
	{
		arg2 = return_bytes(vm->arena, pos, T_REG);
		++pos;
	}
	else
	{
		arg2 = return_bytes(vm->arena, pos, carriage->operation->t_dir_size);
		pos += 2;
	}
	reg_num = vm->arena[pos % MEM_SIZE].value;
	carriage->registers[reg_num] = return_bytes(vm->arena, carriage->position + arg1 + arg2, REG_SIZE);
}

void				op_add(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int8_t	reg1;
	int8_t	reg2;
	int8_t	res_reg;

	reg1 = return_bytes(vm->arena, carriage->position + 2, T_REG) - 1;
	reg2 = return_bytes(vm->arena, carriage->position + 3, T_REG) - 1;
	res_reg = return_bytes(vm->arena, carriage->position + 4, T_REG) - 1;
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

	reg1 = return_bytes(vm->arena, carriage->position + 2, T_REG) - 1;
	reg2 = return_bytes(vm->arena, carriage->position + 3, T_REG) - 1;
	res_reg = return_bytes(vm->arena, carriage->position + 4, T_REG) - 1;
	carriage->registers[res_reg] = carriage->registers[reg1] - carriage->registers[reg2];
	if (carriage->registers[res_reg] == 0)
		carriage->carry = 1;
	else
		carriage->carry = 0;
}

void				op_and(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		position;
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;

	position = carriage->position + 2;
	arg1 = return_bytes(vm->arena, position, type_sizes[arg_code[0] - 1]);
	position += type_sizes[arg_code[0] - 1];
	arg2 = return_bytes(vm->arena, position, type_sizes[arg_code[1] - 1]);
	position += type_sizes[arg_code[1] - 1];
	reg = return_bytes(vm->arena, position, T_REG) - 1;
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	carriage->registers[reg] = arg1 & arg2;
}

void				op_or(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		position;
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;

	position = carriage->position + 2;
	arg1 = return_bytes(vm->arena, position, type_sizes[arg_code[0] - 1]);
	position += type_sizes[arg_code[0] - 1];
	arg2 = return_bytes(vm->arena, position, type_sizes[arg_code[1] - 1]);
	position += type_sizes[arg_code[1] - 1];
	reg = return_bytes(vm->arena, position, T_REG) - 1;
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	carriage->registers[reg] = arg1 | arg2;
}

void				op_xor(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	int32_t		position;
	int32_t		arg1;
	int32_t		arg2;
	uint8_t		reg;

	position = carriage->position + 2;
	arg1 = return_bytes(vm->arena, position, type_sizes[arg_code[0] - 1]);
	position += type_sizes[arg_code[0] - 1];
	arg2 = return_bytes(vm->arena, position, type_sizes[arg_code[1] - 1]);
	position += type_sizes[arg_code[1] - 1];
	reg = return_bytes(vm->arena, position, T_REG) - 1;
	if (arg_code[0] == 3)
		arg1 = return_bytes(vm->arena, (carriage->position + arg1 % IDX_MOD) % MEM_SIZE, 4);
	if (arg_code[1] == 3)
		arg2 = return_bytes(vm->arena, (carriage->position + arg2 % IDX_MOD) % MEM_SIZE, 4);
	carriage->registers[reg] = arg1 ^ arg2;
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
	new_carriage->position = (new_carriage->position + distance % IDX_MOD) % MEM_SIZE;
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
