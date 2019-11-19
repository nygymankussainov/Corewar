/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/11/17 16:01:16 by hfrankly         ###   ########.fr       */
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
	//Introducing
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
