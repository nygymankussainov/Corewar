/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:51:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/28 18:44:21 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_opcode_in_carr(t_major *major, t_carr *carr)
{
	int		i;

	while (carr)
	{
		i = 0;
		if (!carr->dead && !carr->cycles_to_exec)
		{
			while (i < OP_NUMBER)
			{
				if (major->arena[carr->pos] == g_ops[i].opcode)
				{
					carr->op = &g_ops[i];
					carr->cycles_to_exec = g_ops[i].cycles;
					break ;
				}
				carr->cycles_to_exec = 0;
				carr->op = 0;
				carr->opcode = major->arena[carr->pos];
				++i;
			}
		}
		else if (carr->cycles_to_exec > 0)
			--carr->cycles_to_exec;
		carr = carr->next;
	}
}

void	battle(t_carr *carr, t_player *player, t_major *major)
{
	t_carr	*tmp;
	int		cycles_tmp;

	player += 0;
	set_opcode_in_carr(major, carr);
	major->cycles_to_die = CYCLE_TO_DIE;
	cycles_tmp = CYCLE_TO_DIE;
	while (carr)
	{
		tmp = carr;
		while (tmp)
		{
			if (!tmp->cycles_to_exec)
			{
				run_operation(tmp, major);
				set_opcode_in_carr(major, carr);
			}
			--tmp->cycles_to_exec;
			tmp = tmp->next;
		}
		++major->cycles_from_start;
		--cycles_tmp;
		if (major->cycles_to_die <= 0)
	}
}
