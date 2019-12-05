/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:42:02 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 19:43:25 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			parse_dump_flag(t_corewar *vm, char *argv[], int *n)
{
	int			d;

	d = -1;
	if (argv[*n + 1])
		d = ft_atoi(argv[*n + 1]);
	else
		print_usage_and_exit();
	vm->dumps = d;
	*n += 2;
}

void			parse_player(t_corewar *vm, char *argv[], int *n, int player_id)
{
	t_core		*new_player;

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
	if (!argv[*n] || ft_atoi(argv[*n]) < 1 || ft_atoi(argv[*n]) > 4)
		termination_with_error("Invalid player number\n");
	if (!argv[*n + 1])
		termination_with_error("Invalid player name\n");
	player_id = ft_atoi(argv[*n]);
	*n += 1;
	parse_player(vm, argv, n, player_id);
}

void			parse_a_l_flag(t_corewar *vm, char *argv[], int *n)
{
	if (!(ft_strcmp(argv[*n], "-a")))
		vm->flag_a = true;
	else
		vm->flag_l = true;
	*n += 1;
	if (!argv[*n])
		print_usage_and_exit();
}

void			parse_arguments(t_corewar **vm, int argc, char *argv[])
{
	int			n;

	n = 1;
	if (n == argc)
		print_usage_and_exit();
	while (n < argc)
	{
		if (!(ft_strcmp(argv[n], "-dump")))
			parse_dump_flag((*vm), argv, &n);
		else if (!(ft_strcmp(argv[n], "-a")) || !(ft_strcmp(argv[n], "-l")))
			parse_a_l_flag((*vm), argv, &n);
		else if (ft_strcmp(argv[n], "-v") == 0)
		{
			(*vm)->visual = true;
			n++;
		}
		else if (!(ft_strcmp(argv[n], "-n")))
			parse_n_flag(*vm, argv, &n);
		else if (is_name(argv[n]))
			parse_player(*vm, argv, &n, 0);
		else
			termination_with_error("Error\n");
	}
	if ((*vm)->number_of_players < 1 || (*vm)->number_of_players > 4)
		termination_with_error("Wrong number of players\n");
}
