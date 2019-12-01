/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/12/01 20:56:25 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			display_array(t_point *array, uint16_t rows, uint16_t cols)
{
	uint16_t	j;
	uint16_t	i;
	uint16_t	offset;

	i = 0;
	// ft_printf("          0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63\n-------------------------------------------------------------------------------------------------------------------\n");
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

// void			display_array(t_point *array, uint16_t rows, uint16_t cols)
// {
// 	uint16_t	j;
// 	uint16_t	i;
// 	uint16_t	offset;

// 	i = 0;
// 	while (i < rows)
// 	{
// 		j = 0;
// 		offset = i * cols;
// 		while (j < cols)
// 		{
// 			ft_printf("%02x ", array[offset + j].value);
// 			j++;
// 		}
// 		ft_putchar('\n');
// 		i++;
// 	}
// }

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
	//if (vm->visual)
	//	vm->sdl = sdl_init();
	read_byte_code(&vm);
	init_arena(vm);
	introduce_players(vm);
	start_war(vm);
	/*if (vm->visual)
		while (!quit)
		{
			while (SDL_PollEvent(vm->sdl->e) != 0)
				if (vm->sdl->e->type == SDL_QUIT ||
			(vm->sdl->e->type == SDL_KEYDOWN && vm->sdl->e->key.keysym.sym == SDLK_ESCAPE))
					quit = 1;
		}*/
	return (0);
}
