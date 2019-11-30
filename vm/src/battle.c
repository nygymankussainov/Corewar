/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:25:45 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/30 14:16:50 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	review_carrs(t_major *major, t_carr *carr, t_player *player)
{
	while (carr)
	{
		if (carr->cycles_to_exec == 0)
			set_opcode(major, carr);
		if (carr->cycles_to_exec > 0)
			--carr->cycles_to_exec;
		if (carr->cycles_to_exec == 0)
			verify_operation(major, carr, player);
		carr = carr->next;
	}
}

void	battle(t_carr *carr, t_player *player, t_major *major)
{
	player += 0;
	while (major->cycles_to_die > 0 && carr)
	{
		major->cycles_to_die_curr = major->cycles_to_die;
		while (major->cycles_to_die_curr-- > 0)
		{
			review_carrs(major, carr, player);
			++major->cycles_from_start;
		}
		++major->check_count;
		// major->cycles_to_die = check(major, carr);
	}
}
