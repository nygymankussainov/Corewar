/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:26:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 17:08:20 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	create_carriage(t_player *player, t_major *major, int nb, int pos)
{
	t_carr	*new;

	if (!(new = (t_carr *)ft_memalloc(sizeof(t_carr))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (!major->carr)
	{
		major->carr = new;
		major->carr->id = 1;
	}
	else
	{
		new->next = major->carr;
		major->carr = new;
		major->carr->id = major->carr->next->id + 1;
	}
	major->carr->player_id = player[nb].id;
	major->carr->reg[0] = -player[nb].id;
	major->carr->pos = pos;
	player[nb].carr = major->carr;
}

void	vm_init(t_player *player, t_major *major)
{
	int		i;
	int		step;

	i = 0;
	step = MEM_SIZE / major->pl_nb;
	while (i < major->pl_nb)
	{
		ft_memcpy(major->arena + (i * step), player[i].bytecode, \
		player[i].code_size);
		create_carriage(player, major, i, i * step);		
		++i;
	}
}

void	vm(t_player *player, t_major *major)
{
	vm_init(player, major);
	announce_players(player, major->pl_nb);
	battle(player, major);
}
