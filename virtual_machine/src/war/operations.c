#include "virtual_machine.h"

/*
T_REG 01   - 1
T_DIR 10   - 2
T_IND 11   - 3

1:
ld+, ldi+, lld+, lldi+, st+, sti+, and, or, xor
2:
live, add, sub, zjmp, fork, lfork, aff
*/

/*
На операцию live возложены две функции:
1. Она засчитывает, что каретка, которая выполняет операцию live, жива.
2. Если указанный в качестве аргумента операции live номер совпадает с номером игрока, то она засчитывает,
что это игрок жив. Например, если значение аргумента равно -2, значит игрок с номером 2 жив.
*/
void				op_live(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			help;
	uint8_t			player_id;
	//uint32_t		player_id;
	uint16_t		pos = carriage->position + 1;

	carriage->cycle_was_live = vm->current_cycles + vm->total_cycles;
	vm->live_count++;
	//зачемсчитывать 4 байта, если id игрока не может быть длинне одного? считать один байт?
	//player_id = vm->arena[pos % MEM_SIZE] << 24 | vm->arena[(pos + 1) % MEM_SIZE] << 16 | vm->arena[(pos + 2) % MEM_SIZE] << 8 | vm->arena[(pos + 3) % MEM_SIZE];
	player_id = vm->arena[pos % MEM_SIZE];
	//help = player_id >> 24;
	player_id = 256 - player_id;
	if (player_id > 0 && player_id <= vm->number_of_players)
		printf("Player %d (%s) is said to be alive\n", player_id, vm->cores[player_id - 1]->name);

}

/*
Эта операция записывает значение из регистра, который был передан как первый параметр. А вот куда данная операция его записывает, зависит от типа второго аргумента:
Если второй аргумент соответствует типу T_REG, то значение записывается в регистр.
Аргумент #2 — T_IND
Записать значение из регистра, который был передан в качестве первого аргумента, в память по полученному адресу.
*/
void				op_st(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint16_t		arg1;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	reg_num = vm->arena[pos++];

	if (arg_code[1] == 1)
	{
		arg1 = vm->arena[pos % MEM_SIZE];
		carriage->registers[arg1] = carriage->registers[reg_num];
	}
	else
	{
		arg1 = vm->arena[pos % MEM_SIZE] << 8 | vm->arena[(pos + 1) % MEM_SIZE]; //T_IND
		adress = carriage->position + (arg1 % IDX_MOD);
		vm->arena[adress % MEM_SIZE] = carriage->registers[reg_num] << 24;
		vm->arena[(adress + 1) % MEM_SIZE] = carriage->registers[reg_num] << 16;
		vm->arena[(adress + 2) % MEM_SIZE] = carriage->registers[reg_num] << 8;
		vm->arena[(adress + 3) % MEM_SIZE] = carriage->registers[reg_num];
	}
}

/*
Эта операция записывает значение регистра, переданного в качестве первого параметра,
по адресу — текущая позиция + (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТЕГО_АРГУМЕНТА>) % IDX_MOD.
*/
void				op_sti(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint16_t		arg1;
	uint16_t		arg2;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE; //код аргументов уже считан
	reg_num = vm->arena[pos++];
	if (arg_code[1] == 1)
	{	
		arg1 = vm->arena[pos % MEM_SIZE]; //T_REG считываю 1 байт
		++pos;
	}
	else if (arg_code[1] == 2)
	{
		arg1 = vm->arena[pos % MEM_SIZE] << 8 | vm->arena[(pos + 1) % MEM_SIZE]; // T_DIR считываю 2 байта
		pos += 2;
	}
	else
	{
		arg1 = vm->arena[pos % MEM_SIZE] << 8 | vm->arena[(pos + 1) % MEM_SIZE]; //T_IND
		pos += 2;
		adress = carriage->position + (arg1 % IDX_MOD);
		arg1 = vm->arena[adress % MEM_SIZE] << 8 | vm->arena[(adress + 1) % MEM_SIZE];
	}
	if (arg_code[2] == 1)
		arg1 = vm->arena[pos % MEM_SIZE];
	else
		arg2 = vm->arena[pos % MEM_SIZE] << 8 | vm->arena[(pos + 1) % MEM_SIZE];

	vm->arena[carriage->position + (arg1 + arg2) % IDX_MOD] = carriage->registers[reg_num - 1];
	display_array(vm->arena, 64, 64);
}


/*
Данная операция ведет себя практически так же как и операция ld.
То есть записывает значение, полученное из первого аргумента, в регистр, переданный как второй аргумент.
*/
void				op_lld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint32_t		arg1;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 2)
	{
		arg1 = vm->arena[pos] << 24 | vm->arena[(pos + 1) % MEM_SIZE] << 16 | vm->arena[(pos + 2) % MEM_SIZE] << 8 | vm->arena[(pos + 3) % MEM_SIZE];
		pos += 4;
	}
	else
	{
		arg1 = vm->arena[pos] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
		adress = carriage->position + arg1; //Не применяя усечение по модулю
		arg1 = vm->arena[adress % MEM_SIZE] << 24 | vm->arena[(adress + 1) % MEM_SIZE] << 16 | vm->arena[(adress + 2) % MEM_SIZE] << 8 | vm->arena[(adress + 3) % MEM_SIZE];
	}
	reg_num = vm->arena[pos % MEM_SIZE];
	carriage->registers[reg_num] = arg1;
}


/*
Аналогична операции ldi.
Она записывает значение в регистр, который был передан ей как третий параметр.
Значением, которая эта операция записывает, являются считанные 4 байта.
В отличие от операции ldi в этом случае при формировании адреса не нужно делать усечение по модулю IDX_MOD.
*/
void				op_lldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint32_t		arg1;
	uint16_t		arg2;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 1)
		arg1 = vm->arena[pos++];
	else if (arg_code[0] == 2)
	{
		arg1 = vm->arena[pos] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
	}
	else
	{
		arg1 = vm->arena[pos] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
		adress = carriage->position + (arg1 % IDX_MOD);
		//????
		arg1 = vm->arena[adress % MEM_SIZE] << 24 | vm->arena[(adress + 1) % MEM_SIZE] << 16 | vm->arena[(adress + 2) % MEM_SIZE] << 8 | vm->arena[(adress + 3) % MEM_SIZE];
	}
	if (arg_code[1] == 1)
	{
		arg2 = vm->arena[pos % MEM_SIZE];
		++pos;
	}
	else
	{
		arg2 = vm->arena[pos % MEM_SIZE] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
	}
	reg_num = vm->arena[pos % MEM_SIZE];
	adress = carriage->position + (arg1 + arg2);
	carriage->registers[reg_num] = vm->arena[adress % MEM_SIZE] << 24 | vm->arena[(adress + 1) % MEM_SIZE] << 16 | vm->arena[(adress + 2) % MEM_SIZE] << 8 | vm->arena[(adress + 3) % MEM_SIZE];
}

/*
Данная операция записывает значение в регистр, который был ей передан как третий параметр.
Значением, которая она записывает, являются 4 байта. Эти 4 байта она считывает по адресу, который формируется по следующему принципу:
текущая позиция + (<ЗНАЧЕНИЕ_ПЕРВОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА>) % IDX_MOD.
*/
void				op_ldi(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
    uint8_t			reg_num;
	uint32_t		arg1;
	uint16_t		arg2;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 1)
		arg1 = vm->arena[pos++];
	else if (arg_code[0] == 2)
	{
		arg1 = vm->arena[pos] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
	}
	else
	{
		arg1 = vm->arena[pos] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
		adress = carriage->position + (arg1 % IDX_MOD);
		//?????????????????
		arg1 = vm->arena[adress % MEM_SIZE] << 24 | vm->arena[(adress + 1) % MEM_SIZE] << 16 | vm->arena[(adress + 2) % MEM_SIZE] << 8 | vm->arena[(adress + 3) % MEM_SIZE];
		//почему тут считываем 4 байта а не 2???
	}
	if (arg_code[1] == 1)
	{
		arg2 = vm->arena[pos % MEM_SIZE];
		++pos;
	}
	else
	{
		arg2 = vm->arena[pos % MEM_SIZE] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
	}
	reg_num = vm->arena[pos % MEM_SIZE];
	adress = carriage->position + (arg1 + arg2) % IDX_MOD;
	carriage->registers[reg_num] = vm->arena[adress % MEM_SIZE] << 24 | vm->arena[(adress + 1) % MEM_SIZE] << 16 | vm->arena[(adress + 2) % MEM_SIZE] << 8 | vm->arena[(adress + 3) % MEM_SIZE];
}

/*
Задача этой операции состоит в загрузке значения в регистр.
Но её поведение отличается в зависимости от типа первого аргумента:
Если тип первого аргумента это T_DIR, то число переданное в качестве аргумента будет воспринято «как есть».
Если тип первого аргумента это T_IND, то в данном случае число представляет собой адрес.
*/
void				op_ld(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{
	uint8_t			reg_num;
	uint32_t		arg1;
	uint16_t		pos;
	uint16_t		adress;

	pos = (carriage->position + 2) % MEM_SIZE;
	if (arg_code[0] == 2)
	{
		//1. Записать полученное число в регистр, который был передан в качестве второго аргумента.
		arg1 = vm->arena[pos] << 24 | vm->arena[(pos + 1) % MEM_SIZE] << 16 | vm->arena[(pos + 2) % MEM_SIZE] << 8 | vm->arena[(pos + 3) % MEM_SIZE];
		pos += 4;
	}
	else
	{
		//Определить адрес — текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
		//С полученного адреса необходимо считать 4 байта.
		arg1 = vm->arena[pos] << 8 | vm->arena[(pos + 1) % MEM_SIZE];
		pos += 2;
		adress = carriage->position + (arg1 % IDX_MOD);
		arg1 = vm->arena[adress % MEM_SIZE] << 24 | vm->arena[(adress + 1) % MEM_SIZE] << 16 | vm->arena[(adress + 2) % MEM_SIZE] << 8 | vm->arena[(adress + 3) % MEM_SIZE];
	}
	//2. Записать считанное число в регистр, который был передан в качестве второго параметра.
	//3. Если в регистр записали число 0, то устанавливаем значение carry в 1. Если было записано не нулевое значение, то устанавливаем carry в 0.
	reg_num = vm->arena[pos % MEM_SIZE];
	carriage->registers[reg_num] = arg1;
	carriage->carry = (arg1 == 0) ? 1 : 0;

	printf("\n");
	display_array(vm->arena, 64, 64);
}

void				op_add(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_sub(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_and(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_or(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_xor(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_zjmp(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_fork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_lfork(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}

void				op_aff(t_corewar *vm, t_carriage *carriage, int8_t *arg_code)
{

}