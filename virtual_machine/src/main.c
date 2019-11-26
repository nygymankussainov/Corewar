/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: screight <screight@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/11/25 04:01:37 by screight         ###   ########.fr       */
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
		ft_printf("* Player %d, weiging %d bytes, \"%s\" (\"%s\") !\n",
					core->id, core->exec_code_size, core->name, core->comment);
		i++;
	}
}

int				main(int argc, char *argv[])
{
	t_corewar	*vm;
	bool		quit;
	int			i;

	i = 0;
	quit = false;
	vm = init_vm();
	parse_arguments(&vm, argc, argv);
	if (vm->visual)
		vm->sdl = sdl_init();
	read_byte_code(&vm);
	init_arena(vm);
	introduce_players(vm);
	vm->vis_arena = (t_vis_arena*)malloc(sizeof(t_vis_arena) * 4096);
	while (i < 4096)
		vm->vis_arena[i++].is_new = false;
	start_war(vm);
	if (vm->visual)
	{
		while (!quit)
		{
			while (SDL_PollEvent(vm->sdl->e) != 0)
			{
				if (vm->sdl->e->type == SDL_QUIT || (vm->sdl->e->type == SDL_KEYDOWN
									 && vm->sdl->e->key.keysym.sym == SDLK_ESCAPE))
					quit = true;
			}
		}
		ft_close_sdl(vm->sdl);
	}
	return (0);
}
