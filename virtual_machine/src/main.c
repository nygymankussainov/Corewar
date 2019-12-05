/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 16:14:02 by screight         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			display_array(t_point *array, uint16_t rows, uint16_t cols)
{
	uint16_t	j;
	uint16_t	i;
	uint16_t	offset;

	i = 0;
	while (i < rows)
	{
		j = 0;
		offset = i * cols;
		if (offset == 0)
			ft_printf("0x0000 : ");
		else
			ft_printf("%#06x : ", offset);
		while (j < cols)
		{
			if (array[offset + j].value != 0)
				ft_printf("%02x ", array[offset + j].value);
			else
				ft_printf("%02x ", array[offset + j].value);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

void			introduce_players(t_corewar *vm)
{
	uint8_t		i;
	t_core		*core;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->number_of_players)
	{
		core = vm->cores[i];
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					core->id, core->exec_code_size, core->name, core->comment);
		i++;
	}
}

int				main(int argc, char *argv[])
{
	t_corewar	*vm;
	bool		quit;

	quit = false;
	vm = init_vm();
	parse_arguments(&vm, argc, argv);
	if (vm->visual)
		vm->sdl = sdl_init(vm);
	read_byte_code(&vm);
	init_arena(vm);
	introduce_players(vm);
	start_war(vm);
	if (vm->visual)
	{
		while (!quit)
			handle_key_press(vm, &quit, true);
		close_vis(vm, NULL, -1, false);
	}
	free_corewar(vm);
	return (0);
}
