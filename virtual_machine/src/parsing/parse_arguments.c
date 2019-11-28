#include "virtual_machine.h"

void 			parse_dump_flag(t_corewar *vm, char *argv[], int *n)
{
	vm->dumps = ft_atoi(argv[*n] + 6);
	(*n)++;
}

int 			is_name(t_corewar *vm, char *str)
{
	char 		*ptr;

	if (!(ptr = ft_strstr(str, ".cor")))
		terminate_with_error(vm);
	return (1);
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
	{
		if (new_player->id == 0)
		{
			core_tmp = vm->line_of_players;
			while (core_tmp->next)
				core_tmp = core_tmp->next;
			core_tmp->next = new_player;
		}
		else
		{
			new_player->next = vm->line_of_players;
			vm->line_of_players = new_player;
		}
	}
	*n += 1;
	vm->number_of_players++;
}

void			parse_n_flag(t_corewar *vm, char *argv[], int *n)
{
	int player_id;

	*n += 1;
	if (!argv[*n] || ft_atoi(argv[*n]) < 1 || ft_atoi(argv[*n]) > 4 || !argv[*n + 1])
		terminate_with_error(vm);
	player_id = ft_atoi(argv[*n]);
	*n += 1;
	parse_player(vm, argv, n, player_id);
}

void			parse_arguments(t_corewar **vm, int argc, char *argv[])
{
	int 		n;

	n = 1;
	while (n < argc)
	{
		if (ft_strstr(argv[n], "-dump"))
			parse_dump_flag((*vm), argv, &n);
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
	if ((*vm)->number_of_players < 2 || (*vm)->number_of_players > 4)
		terminate_with_error((*vm));
	(*vm)->winner = (*vm)->cores[(*vm)->number_of_players - 1];
}