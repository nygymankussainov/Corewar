/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:08:05 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/30 13:56:13 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	delete_player(t_player *player, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (player[i].name)
			ft_strdel(&player[i].name);
		if (player[i].comment)
			ft_strdel(&player[i].comment);
		if (player[i].bytecode)
			ft_strdel(&player[i].bytecode);
		i++;
	}
	free(player);
	player = NULL;
}

int		check_flag_format(char **argv, int i)
{
	if (!ft_isdigit(*argv[i]) || (ft_isdigit(*argv[i]) &&
	ft_strcmp(argv[i - 1], "-n") && ft_strcmp(argv[i - 1], "-dump")))
	{
		putstrerr("Invalid argument ");
		putstrerr(argv[i]);
		putstrerr("\n");
		return (0);
	}
	return (1);
}

int		validate_players(int argc, char **argv, t_player *player, int nb)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (isplayer(argv[i]))
		{
			if (!check_bytecode(argv[i], player, nb, j++))
				return (0);
		}
		else if (ft_strcmp(argv[i], "-n") && ft_strcmp(argv[i], "-dump"))
		{
			if (!check_flag_format(argv, i))
				return (0);
		}
		else if ((!ft_strcmp(argv[i], "-n") || !ft_strcmp(argv[i], "-dump"))
		&& !ft_isdigit(*argv[i + 1]))
		{
			putstrerr("Wrong flag format\n");
			return (0);
		}
		++i;
	}
	return (1);
}

t_player	*validation(int argc, char **argv, int nb)
{
	t_player *player;

	if (!(player = (t_player *)ft_memalloc(sizeof(t_player) * nb)))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (!validate_players(argc, argv, player, nb))
		return (0);
	if (argc - 1 != nb)
		modify_players_id(player, argv, argc, nb);
	return (player);
}
