/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/11/09 13:48:34 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			display_array(uint8_t *array, uint16_t rows, uint16_t cols)
{
	uint16_t	j;
	uint16_t	i;
	uint16_t	offset;

	i = 0;
	while (i < rows)
	{
		j = 0;
		offset = i * cols;
		while (j < cols)
		{
			if (array[offset + j] != 0)
				ft_printf("\e[1;34m%02x\e[m ", array[offset + j]);
			else
				ft_printf("%02x ", array[offset + j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int				main(int argc, char *argv[])
{
	t_corewar	*vm;

	vm = init_vm();
	parse_arguments(vm, argc, argv);
	read_byte_code(vm);
	init_arena(vm);
	display_array(vm->arena, 64, 64);
	//Introducing
	start_war(vm);
	return (0);
}
