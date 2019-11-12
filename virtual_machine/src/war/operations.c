#include "virtual_machine.h"

/*
T_REG 01   - 1
T_DIR 10   - 2
T_IND 11   - 3

1:
ld, ldi, lld, lldi, st, sti, and, or, xor
2:
live, add, sub, zjmp, fork, lfork, aff
*/


/*
есть код типов аргументов
Эта операция записывает значение регистра, переданного в качестве первого параметра,
по адресу — текущая позиция + (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
*/
void				op_sti(t_corewar *vm, t_carriage *carriage)
{
    uint32_t        args[3];
	uint16_t		args_byte_code; //01 10 10 00

	uint8_t			reg_num;
	uint16_t		arg1;
	uint16_t		arg2;

	uint16_t		pos = carriage->position + 1;

	args_byte_code = vm->arena[pos++];
	printf("%hu\n", args_byte_code);
	//if (args_byte_code & 3 != 0) ошибка

	args[0] = args_byte_code >> 6 & 3;
	args[1] = args_byte_code >> 4 & 3;
	args[2] = args_byte_code >> 2 & 3;
	//if (args[0] & op_array[10].args_types[0] == 0 || args[1] & op_array[10].args_types[1] == 0 || args[2] & op_array[10].args_types[2])
	//ошибка в коде аргументов
	
	reg_num = vm->arena[pos++];
	printf("%hhu\n", reg_num);

	arg1 = vm->arena[pos] << 8 | vm->arena[pos + 1];
	pos += 2;
	printf("%hu\n", arg1);

	arg2 = vm->arena[pos] << 8 | vm->arena[pos + 1];
	printf("%hu\n", arg2);

	vm->arena[carriage->position + arg1 + arg2] = carriage->registers[reg_num - 1];
	carriage->position += 1 + 1 + args[1] + args[2] + 1;
	display_array(vm->arena, 64, 64);
    //считать код аргументов, записать их в args /пример: 68 - 01 10 10 00
	//зная сколько байт занимает значение каждого аргумента получить значения и выполнить операцию


}


/*
На операцию live возложены две функции:
1. Она засчитывает, что каретка, которая выполняет операцию live, жива.
2. Если указанный в качестве аргумента операции live номер совпадает с номером игрока, то она засчитывает,
что это игрок жив. Например, если значение аргумента равно -2, значит игрок с номером 2 жив.
*/
void				op_live(t_corewar *vm, t_carriage *carriage)
{
	uint16_t		player_id;
	uint16_t		pos = carriage->position + 1;

	carriage->cycle_was_live = vm->total_cycles;
	vm->live_count++;
	player_id = vm->arena[pos] << 8 | vm->arena[pos + 1];

}

void				op_ld(t_corewar *vm, t_carriage *carriage)
{

}

void				op_st(t_corewar *vm, t_carriage *carriage)
{

}

void				op_add(t_corewar *vm, t_carriage *carriage)
{

}

void				op_sub(t_corewar *vm, t_carriage *carriage)
{

}

void				op_and(t_corewar *vm, t_carriage *carriage)
{

}

void				op_or(t_corewar *vm, t_carriage *carriage)
{

}

void				op_xor(t_corewar *vm, t_carriage *carriage)
{

}

void				op_zjmp(t_corewar *vm, t_carriage *carriage)
{

}

void				op_ldi(t_corewar *vm, t_carriage *carriage)
{

}

void				op_fork(t_corewar *vm, t_carriage *carriage)
{

}

void				op_lld(t_corewar *vm, t_carriage *carriage)
{

}

void				op_lldi(t_corewar *vm, t_carriage *carriage)
{

}

void				op_lfork(t_corewar *vm, t_carriage *carriage)
{

}

void				op_aff(t_corewar *vm, t_carriage *carriage)
{

}