/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:51:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 21:37:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_opcode_in_carr(t_major *major)
{
	t_carr	*carr;
	int		i;

	carr = major->carr;
	while (carr)
	{
		i = 0;
		if (!carr->dead && !carr->cycles_to_exec)
		{
			while (i < OP_NUMBER)
			{
				if (major->arena[carr->pos] == g_ops[i].opcode_char)
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
		else
			--carr->cycles_to_exec;
		carr = carr->next;
	}
}

void	battle(t_player *player, t_major *major)
{
	set_opcode_in_carr(major);
}
