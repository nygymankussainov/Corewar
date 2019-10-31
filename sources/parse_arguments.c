/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:49:05 by egiant            #+#    #+#             */
/*   Updated: 2019/10/31 18:22:21 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void 			parse_dump_flag(t_vm *vm, char *argv[], int *n)
{
	return ;
}

int 			is_name(t_vm *vm, char *str)
{
	//каких символов не может быть в имени игрока?
	char 		*ptr;

	if (!(ptr = ft_strstr(str, ".cor")))
		terminate_with_error(vm);
	//проверить что после .cor нет символов
	return (1);
}

void 			parse_player(t_vm *vm, char *argv[], int *n)
{
	int			num;
	char		**name;
	t_player	*p_ptr;

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
		if (vm->players[num])
			terminate_with_error(vm);
		vm->players[num] = (t_player *)malloc(sizeof(t_player));
		init_player(vm->players[num]);
		vm->players[num]->name = ft_strdup(name[0]);
		vm->players[num]->number = num + 1;
		*n += 3;
	}
	else
	{
		name = ft_strsplit(argv[*n], '.');
		if (!vm->line_of_players)
		{
			vm->line_of_players = (t_player *)malloc(sizeof(t_player));
			p_ptr = vm->line_of_players;
		}
		else
		{
			p_ptr = vm->line_of_players;
			while (p_ptr->next)
				p_ptr = p_ptr->next;
			p_ptr->next = (t_player *)malloc(sizeof(t_player));
			p_ptr = p_ptr->next;
		}
		init_player(p_ptr);
		p_ptr->name = ft_strdup(name[0]);
		*n += 1;
	}
	vm->number_of_players++;	
}

void 			add_remaining_players(t_vm *vm)
{
	int			n;
	int			num;

	n = 0;
	num = vm->number_of_players;
	while (n < 4 && vm->line_of_players)
	{
		if (!vm->players[n])
		{
			vm->players[n] = vm->line_of_players; //проверить не потеряю ли я выделенную память
			vm->players[n]->number = n + 1;
			vm->line_of_players = vm->line_of_players->next;
		}
		++n;
		--num;
	}
	if (!vm->players[n] && num != 0)
		terminate_with_error(vm);
}

void			parse_arguments(t_vm *vm, int argc, char *argv[]) //+ флаг визуализации
{
	int 		n;

	n = 1;
	while (n < argc)
	{
		if (!ft_strcmp(argv[n], "-dump"))
			parse_dump_flag(vm, argv, &n);
		else if (!ft_strcmp(argv[n], "-n") || is_name(vm, argv[n]))
			parse_player(vm, argv, &n);
	}
	if (vm->number_of_players < 2) //2?
		terminate_with_error(vm);
	if (vm->line_of_players)
		add_remaining_players(vm);
}

//проверить валидность игроков:
//номера идут подрят, номера не повторяются, номер после -n < 4