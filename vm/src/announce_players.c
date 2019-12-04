/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:57:57 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/04 22:28:44 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_dump(char *arena)
{
	int		i;
	int		j;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!i)
			ft_printf("0x");
		ft_printf("%#.4x : ", i);
		j = 0;
		while (j < 64)
		{
			ft_printf("%.2x ", (u_int8_t)arena[j + i]);
			++j;
		}
		printf("\n");
		i += 64;
	}
}

void	announce_players(t_player *player, int nb)
{
	int		i;

	i = 0;
	ft_printf("%s\n", "Introducing contestants...");
	while (i < nb)
	{
		ft_printf("* Player %d, ", player[i].id);
		ft_printf("weighing %d bytes, ", player[i].code_size);
		ft_printf("\"%s\" ", player[i].name);
		ft_printf("(\"%s\") !\n", player[i].comment);
		i++;
	}
}
