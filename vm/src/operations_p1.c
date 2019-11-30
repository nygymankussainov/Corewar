/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:43:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/30 17:06:54 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ld(t_major *major, t_carr *carr, t_player *player)
{
	int		i;
	int		value;
	char	address[carr->op->t_dir_size + 1];

	value = major->args[0];
	i = 0;
	if (major->args_type[0] == IND_CODE)
	{
		value %= IDX_MOD;
		while (i < carr->op->t_dir_size)
		{
			address[i] = major->arena[value % MEM_SIZE];
			++i;
		}
		address[i] = '\0';
		value = *((int *)address);
	}
	carr->reg[major->args[1] - 1] = value;
	carr->carry = value == 0 ? 1 : 0;
}

int		live(t_major *major, t_carr *carr, t_player *player)
{
	++carr->live_count;
	++major->live_count;
	carr->lastlive_cycle = major->cycles_from_start;
	major->args[0] *= -1;
	if (major->args[0] >= 1 && major->args[0] <= major->pl_nb)
		major->lastlive = &player[major->args[0] - 1];
	return (0);
}
