/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_players_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:29:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/26 20:54:12 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	delete_players_id(t_player *player, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		player[i].id = 0;
		i++;
	}
}

int		isreserved(int check, t_player *player, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (player[i].id == check)
			return (1);
		i++;
	}
	return (0);
}

void	modify_players_id(t_player *player, int nb, int tmp, int reserve)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (!player[i].id)
		{
			if (i + 1 != reserve)
				player[i].id = i + 1;
			else
				player[i].id = tmp;	
		}
		i++;
	}
	ft_printf("\n");
}

int		find_flag(t_player *player, char **argv, int argc, int nb)
{
	int		i;
	int		reserve;

	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-n"))
		{
			reserve = ft_atoi(argv[i + 1]);
			if (reserve <= 0 || reserve > 4)
			{
				ft_printf("%d ", reserve);
				putstrerr("is not a valid number for a champion\n");
				return (0);
			}
			ft_swap(&player[i - 1].id, &player[reserve - 1].id);
		}
		i++;
	}
	i = 0;
	while (i < nb)
	{
		ft_printf("%d)%s ", player[i].id, player[i].name);
		i++;
	}
	return (1);
}
