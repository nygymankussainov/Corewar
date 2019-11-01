/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/11/01 16:09:16 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int				main(int argc, char *argv[])
{
	t_corewar	*vm;

	//if (argc > 2)
	//{
		vm = init_vm();
		parse_arguments(vm, argc, argv);
		read_byte_code(vm);
		//init_arena(vm);
	/*}
	else
	{
		return (0);
		//нет аргументов или один аргумент
	}*/
	return (0);
}

/*typedef struct		s_cursor
{
	current_place;
	carry;
	parent_number;
	register[16];
	live;
	command;
	cycle_to_die; ?
}					t_cursor;*/