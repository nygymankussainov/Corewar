/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_players_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:29:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 13:54:17 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sort_players(t_player *player, int nb, int reserve)
{
	int		i;

	while (nb)
	{
		i = 0;
		while (i < nb)
		{
			if (player[i].id != reserve)
			{
				if (i + 1 < nb && player[i + 1].id != reserve)
				{
					if (i + 1 < nb && player[i].id > player[i + 1].id)
						ft_swap(&player[i].id, &player[i + 1].id);
				}
				else if (i + 2 < nb && player[i].id > player[i + 2].id)
				{
					ft_swap(&player[i].id, &player[i + 2].id);
					++i;
				}
			}
			++i;
			i >= nb - 1 ? --nb : nb;
		}
	}
}

int		find_player(t_player *player, int reserve, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (player[i].id == reserve)
			return (i);
		i++;
	}
	return (i);
}

void	modify_players_id(t_player *player, char **argv, int argc, int nb)
{
	int		i;
	int		j;
	int		tmp;
	int		reserve;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (isplayer(argv[i]))
			++j;
		if (!ft_strcmp(argv[i], "-n"))
		{
			reserve = ft_atoi(argv[i + 1]);
			if (reserve <= 0 || reserve > nb)
				return ;
			tmp = find_player(player, reserve, nb);
			ft_swap(&player[j].id, &player[tmp].id);
			sort_players(player, nb, reserve);
		}
		i++;
	}
	i = 0;
	while (i < nb)
	{
		ft_printf("%d)%s ", player[i].id, player[i].name);
		i++;
	}
}
