/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:13:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/05 18:41:44 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_pos(int pos)
{
	pos = pos % MEM_SIZE;
	if (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

void	verify_operation(t_vm *vm, t_carr *carr)
{
	int		skip;
	int		verification;

	carr->skip = carr_move(carr, 1);
	if (carr->opcode >= vm->first_op &&
		carr->opcode <= vm->last_op)
	{
		if (carr->op->args_type_code)
		{
			get_arg_types(vm, carr);
			carr->skip += carr_move(carr, 1);
		}
		verification = verify_args(vm, carr);
		if (verification)
			carr->op->f(vm, carr);
		if (!verification || carr->op->f != zjmp)
		{
			skip = skip_args(vm, carr, carr->op->args_number, 1);
			carr_move(carr, skip);
		}
	}
}
