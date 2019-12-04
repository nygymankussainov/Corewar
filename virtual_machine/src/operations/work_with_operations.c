/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:37:50 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/04 18:39:49 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

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

int32_t				return_arg(t_point *arena, uint16_t *position,
								uint8_t arg_code, uint8_t t_dir_size)
{
	int8_t		reg;
	int16_t		ind;
	int16_t		dir16;
	int32_t		dir32;
	
	if (arg_code == 1)
	{
		reg = return_bytes(arena, *position, 1) - 1;
		*position = (*position + 1) % MEM_SIZE;
		return (reg);
	}
	else if (arg_code == 3)
	{
		ind = return_bytes(arena, *position, 2);
		*position = (*position + 2) % MEM_SIZE;
		return (ind);
	}
	else if (t_dir_size == 2)
	{
		dir16 = return_bytes(arena, *position, 2);
		*position = (*position + 2) % MEM_SIZE;
		return (dir16);
	}
	else
	{
		dir32 = return_bytes(arena, *position, 4);
		*position = (*position + 4) % MEM_SIZE;
		return (dir32);
	}
}

uint16_t			get_position(uint16_t cur_pos, int64_t arg, bool idx)
{
	int8_t	sign;
	int32_t	res;

	if (arg < 0)
	{
		arg = -arg;
		sign = -1;
	}
	else
		sign = 1;
	if (idx)
		res = cur_pos + sign * (arg % IDX_MOD);
	else
		res = cur_pos + sign * arg;
	if (res < 0)
	{
		res = -res;
		res = MEM_SIZE - (res % MEM_SIZE);
	}
	return (res % MEM_SIZE);
}

void				add_to_arena(t_corewar *vm, uint16_t position, int32_t code, t_carriage *carriage)
{
	vm->arena[position].value = code >> 24;
	vm->arena[(position + 1) % MEM_SIZE].value = code >> 16 & 0x00FF;
	vm->arena[(position + 2) % MEM_SIZE].value = code >> 8 & 0x0000FF;
	vm->arena[(position + 3) % MEM_SIZE].value = code & 0x000000FF;
	vm->arena[position].color = carriage->color;
	vm->arena[(position + 1) % MEM_SIZE].color = carriage->color;
	vm->arena[(position + 2) % MEM_SIZE].color = carriage->color;
	vm->arena[(position + 3) % MEM_SIZE].color = carriage->color;
	vm->arena[position].light_count = 51;
	vm->arena[(position + 1) % MEM_SIZE].light_count = 51;
	vm->arena[(position + 2) % MEM_SIZE].light_count = 51;
	vm->arena[(position + 3) % MEM_SIZE].light_count = 51;
	carriage->last_operation[0] = position;
	carriage->last_operation[1] = (position + 1) % MEM_SIZE;
	carriage->last_operation[2] = (position + 2) % MEM_SIZE;
	carriage->last_operation[3] = (position + 3) % MEM_SIZE;
}