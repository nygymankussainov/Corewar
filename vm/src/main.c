/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:03:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 17:00:27 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		isplayer(char *str)
{
	if (ft_strstr(str, ".cor"))
		return (1);
	return (0);
}

int		count_players(int argc, char **argv)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (isplayer(argv[i]))
			count++;
		i++;
	}
	return (count);
}

int		print_usage(void)
{
	ft_printf("%s\n", "Usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor]");
	return (0);
}

t_major	*init_major(char **argv, int argc, int nb, t_player *player)
{
	t_major	*major;

	if (!(major = (t_major *)ft_memalloc(sizeof(t_major))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	major->pl_nb = nb;
	major->lastlive = &player[nb - 1];
	major->cycles_to_die = CYCLE_TO_DIE;
	while (argc--)
	{
		if (!ft_strcmp(argv[argc], "-dump"))
		{
			major->dump = ft_atoi(argv[argc + 1]);
			major->dump = major->dump < 0 ? 0 : major->dump;
			return (major);
		}
	}
	return (major);
}

int		main(int argc, char **argv)
{
	int			nb;
	t_player	*player;
	t_major		*major;

	if (argc < 2)
		return (print_usage());
	nb = count_players(argc, argv);
	if (nb > MAX_PLAYERS)
		putstrerr("Too many champions\n");
	else if ((player = validation(argc, argv, nb)) != NULL)
	{
		major = init_major(argv, argc, nb, player);
		vm(player, major);
		delete_player(player, nb);
		return (1);
	}
	return (0);
}
