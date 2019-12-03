/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:13:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 13:27:16 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	verify_operation(t_vm *vm, t_carr *carr)
{
	carr_move(carr, 1);
	if (carr->opcode >= vm->first_op &&
		carr->opcode <= vm->last_op)
	{
		if (carr->op->args_type_code)
		{
			get_arg_types(vm, carr);
			carr_move(carr, 1);
		}
		if (verify_args(vm, carr))
		{
			if (!carr->op->f)
				carr->op->f = g_op_funcs[(int)carr->opcode - 1].f;
			carr->op->f(vm, carr);
		}
		if (carr->op->f != zjmp)
			carr_move(carr, skip_args(vm, carr, carr->op->args_number, 1));
	}
}
