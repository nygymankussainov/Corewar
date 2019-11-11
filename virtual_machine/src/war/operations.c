#include "virtual_machine.h"

/*
T_REG 01
T_DIR 10
T_IND 11

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
void				op_sti(t_corewar *vm, uint16_t position)
{
    uint32_t        args[3];
	uint16_t		args_byte_code;

	args_byte_code = vm->arena[position];
	printf("%hu\n", args_byte_code);
    //считать код аргументов, записать их в args /пример: 68 - 01 10 10 00
    //T_REG всегда 1й аргумент, 
	//зная сколько байт занимает значение каждого аргумента получить значения и выполнить операцию


}

void				op_live(t_corewar *vm, uint16_t position)
{

}

void				op_ld(t_corewar *vm, uint16_t position)
{

}

void				op_st(t_corewar *vm, uint16_t position)
{

}

void				op_add(t_corewar *vm, uint16_t position)
{

}

void				op_sub(t_corewar *vm, uint16_t position)
{

}

void				op_and(t_corewar *vm, uint16_t position)
{

}

void				op_or(t_corewar *vm, uint16_t position)
{

}

void				op_xor(t_corewar *vm, uint16_t position)
{

}

void				op_zjmp(t_corewar *vm, uint16_t position)
{

}

void				op_ldi(t_corewar *vm, uint16_t position)
{

}

void				op_fork(t_corewar *vm, uint16_t position)
{

}

void				op_lld(t_corewar *vm, uint16_t position)
{

}

void				op_lldi(t_corewar *vm, uint16_t position)
{

}

void				op_lfork(t_corewar *vm, uint16_t position)
{

}

void				op_aff(t_corewar *vm, uint16_t position)
{

}