/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:13:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/01 18:30:02 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_reg(t_vm *vm, t_carr *carr, int size)
{
	int32_t		reg;

	reg = (int32_t)vm->arena[(carr->pos + size) % MEM_SIZE];
	if (reg > 0 && reg <= OP_NUMBER)
		return (1);
	return (0);
}

int		skip_args(t_vm *vm, t_carr *carr, int arg_nb, bool del_arg)
{
	int		bytes;
	int		i;

	bytes = 0;
	i = 0;
	while (i < arg_nb)
	{
		if (vm->args_type[i] == REG_CODE ||
		(!vm->args_type[i] && carr->op->args_type[i] == T_REG))
			++bytes;
		else if (vm->args_type[i] == DIR_CODE ||
		(!vm->args_type[i] && carr->op->args_type[i] == T_DIR))
			bytes += carr->op->t_dir_size;
		else
			bytes += IND_SIZE;
		vm->args_type[i] = del_arg ? '\0' : vm->args_type[i];
		vm->args[i] = del_arg ? 0 : vm->args[i];
		++i;
	}
	return (bytes);
}

int		get_args_type_code_size(t_vm *vm, t_carr *carr, int i, int size)
{
	if (((carr->op->args_type[i] & T_REG && vm->args_type[i] == REG_CODE)
	&& check_reg(vm, carr, size)))
		return (1);
	else if (carr->op->args_type[i] & T_DIR && vm->args_type[i] == DIR_CODE)
		return (carr->op->t_dir_size);
	else if (carr->op->args_type[i] & T_IND && vm->args_type[i] == IND_CODE)
		return (IND_SIZE);
	return (0);
}

int		get_arg_size(t_carr *carr, int i)
{
	if (carr->op->args_type[i] == T_REG)
		return (REG_SIZE);
	else if (carr->op->args_type[i] == T_DIR)
		return (carr->op->t_dir_size);
	return (IND_SIZE);
}

int		verify_args(t_vm *vm, t_carr *carr)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (i < carr->op->args_number)
	{
		if (carr->op->args_type_code)
		{
			size = get_args_type_code_size(vm, carr, i, size);
			if (!size)
				return (0);
		}
		else
			size = get_arg_size(carr, i);
		get_args_value(vm, carr, i, size);
		++i;
	}
	return (1);
}
