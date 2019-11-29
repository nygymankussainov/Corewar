/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:26:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/29 16:31:30 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	create_carriage(t_player *player, t_carr **carr, int pos)
{
	t_carr	*new;

	if (!(new = (t_carr *)ft_memalloc(sizeof(t_carr))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (!*carr)
	{
		*carr = new;
		(*carr)->id = 1;
	}
	else
	{
		new->next = *carr;
		(*carr)->prev = new;
		*carr = new;
		(*carr)->id = (*carr)->next->id + 1;
	}
	(*carr)->player_id = player->id;
	(*carr)->reg[0] = -player->id;
	(*carr)->pos = pos;
}

t_carr	*vm_init(t_player *player, t_major *major)
{
	int		i;
	int		step;
	t_carr	*carr;

	i = 0;
	step = MEM_SIZE / major->pl_nb;
	carr = NULL;
	while (i < major->pl_nb)
	{
		ft_memcpy(major->arena + (i * step), player[i].bytecode, \
		player[i].code_size);
		create_carriage(&player[i], &carr, i * step);		
		++i;
	}
	return (carr);
}

void	vm(t_player *player, t_major *major)
{
	t_carr	*carr;

	carr = vm_init(player, major);
	major->lastlive = &player[major->pl_nb - 1];
	announce_players(player, major->pl_nb);
	// int fd = open("test", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	// write(fd, major->arena, MEM_SIZE);
	battle(carr, player, major);
}
