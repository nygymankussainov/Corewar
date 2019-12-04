/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:42:02 by egiant            #+#    #+#             */
/*   Updated: 2019/12/04 18:06:47 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			parse_dump_flag(t_corewar *vm, char *argv[], int *n)
{
	int			d;

	if (argv[*n + 1])
		d = ft_atoi(argv[*n + 1]);
	else
		terminate_with_error(vm);
	vm->dumps = d;
	*n += 2;
}

void			parse_player(t_corewar *vm, char *argv[], int *n, int player_id)
{
	t_core		*new_player;
	t_core		*core_tmp;

	if (!(new_player = (t_core*)malloc(sizeof(t_core))))
		termination_with_perror("Parse player error", ENOMEM);
	init_core(new_player);
	new_player->executable_file_name = ft_strdup(argv[*n]);
	new_player->id = player_id;
	if (!vm->line_of_players)
		vm->line_of_players = new_player;
	else
		add_player_to_list(vm, new_player);
	*n += 1;
	vm->number_of_players++;
}

void			parse_n_flag(t_corewar *vm, char *argv[], int *n)
{
	int			player_id;

	*n += 1;
	if (!argv[*n] || ft_atoi(argv[*n]) < 1 || ft_atoi(argv[*n]) > 4
			|| !argv[*n + 1])
		terminate_with_error(vm);
	player_id = ft_atoi(argv[*n]);
	*n += 1;
	parse_player(vm, argv, n, player_id);
}

void			parse_a_flag(t_corewar *vm, char *argv[], int *n)
{
	*n += 1;
	vm->flag_a = true;
}

void			parse_arguments(t_corewar **vm, int argc, char *argv[])
{
	int			n;

	n = 1;
	while (n < argc)
	{
		if (!(ft_strcmp(argv[n], "-dump")))
			parse_dump_flag((*vm), argv, &n);
		else if (!(ft_strcmp(argv[n], "-a")))
			parse_a_flag((*vm), argv, &n);
		else if (ft_strcmp(argv[n], "-v") == 0)
		{
			(*vm)->visual = true;
			n++;
		}
		else if (!(ft_strcmp(argv[n], "-n")))
			parse_n_flag(*vm, argv, &n);
		else if (is_name(*vm, argv[n]))
			parse_player(*vm, argv, &n, 0);
		else
			terminate_with_error((*vm));
	}
	if ((*vm)->number_of_players < 1 || (*vm)->number_of_players > 4)
		terminate_with_error((*vm));
}
