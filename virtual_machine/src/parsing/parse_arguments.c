/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:49:05 by egiant            #+#    #+#             */
/*   Updated: 2019/11/13 14:12:19 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void 			parse_dump_flag(t_corewar *vm, char *argv[], int *n)
{
	return ;
}

int 			is_name(t_corewar *vm, char *str)
{
	//каких символов не может быть в имени игрока?
	char 		*ptr;

	if (!(ptr = ft_strstr(str, ".cor")))
		terminate_with_error(vm);
	//проверить что после .cor нет символов
	return (1);
}

void 			parse_player(t_corewar *vm, char *argv[], int *n)
{
	int			num;
	char		**name;
	t_core		*p_ptr;

	if (!ft_strcmp(argv[*n], "-n"))
	{
		if (!argv[*n + 1] || !argv[*n + 2])
			terminate_with_error(vm);
		//проверить что это именно число
		num = ft_atoi(argv[*n + 1]);
		if (num > 4)
			terminate_with_error(vm);
		is_name(vm, argv[*n + 2]);
		name = ft_strsplit(argv[*n + 2], '.');
		--num;
		if (vm->cores[num])
			terminate_with_error(vm);
		vm->cores[num] = (t_core *)malloc(sizeof(t_core));
		init_core(vm->cores[num]);
		ft_strcpy(vm->cores[num]->name, name[0]);
		vm->cores[num]->id = num + 1;
		free(name);
		*n += 3;
	}
	else
	{
		name = ft_strsplit(argv[*n], '.');
		if (!vm->line_of_players)
		{
			vm->line_of_players = (t_core *)malloc(sizeof(t_core));
			p_ptr = vm->line_of_players;
		}
		else
		{
			p_ptr = vm->line_of_players;
			while (p_ptr->next)
				p_ptr = p_ptr->next;
			p_ptr->next = (t_core *)malloc(sizeof(t_core));
			p_ptr = p_ptr->next;
		}
		init_core(p_ptr);
		ft_strcpy(p_ptr->name , name[0]);
		free(name);
		*n += 1;
	}
	vm->number_of_players++;
}

void 			add_remaining_players(t_corewar *vm)
{
	int			n;
	int			num;

	n = 0;
	num = vm->number_of_players;
	while (n < 4 && vm->line_of_players)
	{
		if (!vm->cores[n])
		{
			vm->cores[n] = vm->line_of_players; //проверить не потеряю ли я выделенную память
			vm->cores[n]->id = n + 1;
			vm->line_of_players = vm->line_of_players->next;
		}
		++n;
		--num;
	}
	if (!vm->cores[n] && num != 0)
		terminate_with_error(vm);
}

void			parse_arguments(t_corewar *vm, int argc, char *argv[]) //+ флаг визуализации
{
	int 		n;

	n = 1;
	while (n < argc)
	{
		if (ft_strequ(argv[n], "-dump"))
			parse_dump_flag(vm, argv, &n);
		else if (ft_strequ(argv[n], "-n") || is_name(vm, argv[n]))
			parse_player(vm, argv, &n);
	}
	if (vm->number_of_players < 2)
		terminate_with_error(vm);
	if (vm->line_of_players)
		add_remaining_players(vm);
	vm->winner = vm->cores[vm->number_of_players - 1];
}

//проверить валидность игроков:
//номера идут подрят, номера не повторяются, номер после -n < 4