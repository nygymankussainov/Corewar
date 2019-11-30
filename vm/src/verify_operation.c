/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:13:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/30 14:50:40 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_reg(t_major *major, t_carr *carr, int arg_nb)
{
	int32_t		reg;

	reg = (int32_t)major->arena[(carr->pos + arg_nb) % MEM_SIZE];
	if (reg > 0 && reg <= OP_NUMBER)
		return (1);
	return (0);
}

void	skip_args(t_major *major, t_carr *carr)
{
	int		bytes;
	int		i;

	bytes = 0;
	i = 0;
	while (i < carr->op->args_number)
	{
		if (major->args_type[i] == REG_CODE)
			++bytes;
		else if (major->args_type[i] == DIR_CODE)
			bytes += carr->op->t_dir_size;
		else
			bytes += IND_SIZE;
		major->args_type[i] = '\0';
		++i;
	}
	carr_move(carr, bytes);
}

int		check_arg(t_major *major, t_carr *carr, int i)
{
	if (((carr->op->args_type[i] & T_REG && major->args_type[i] == REG_CODE)
	&& check_reg(major, carr, i)) ||
	(carr->op->args_type[i] & T_DIR && major->args_type[i] == DIR_CODE) ||
	(carr->op->args_type[i] & T_IND && major->args_type[i] == IND_CODE))
		return (1);
	return (0);
}

int		check_args_type_code(t_major *major, t_carr *carr)
{
	int		i;

	i = 0;
	if (carr->op->args_type_code)
	{
		get_arg_types(major, carr);
		carr_move(carr, 1);
		while (i < carr->op->args_number)
		{
			if (!check_arg(major, carr, i))
				return (0);
			++i;
		}
	}
	return (1);
}

void	verify_operation(t_major *major, t_carr *carr, t_player *player)
{
	player += 0;
	carr_move(carr, 1);
	if (carr->opcode >= major->first_op &&
		carr->opcode <= major->last_op)
	{
		if (check_args_type_code(major, carr))
		{
			// execute_operation(major, carr, player);
			carr->pos += carr->step_to_next_op;
		}
		else
			skip_args(major, carr);
	}
}
