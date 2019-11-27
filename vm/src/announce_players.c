/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:57:57 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 17:05:45 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
