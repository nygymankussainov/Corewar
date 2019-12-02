/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:13:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/02 10:31:12 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_ind_value(t_vm *vm, t_carr *carr, int pos, int size)
{
	char	*address;
	int		i;
	int		value;

	i = 0;
	if (!(address = (char *)ft_memalloc(sizeof(char) * size + 1)))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	while (i < size)
	{
		address[i] = vm->arena[(carr->pos + pos + i) % MEM_SIZE];
		++i;
	}
	address = rev_bytes(address, size);
	i = 0;
	while (!address[i] && i < size)
		++i;
	value = *((int *)(address + i));
	ft_strdel(&address);
	return (value);
}

void	verify_operation(t_vm *vm, t_carr *carr, t_player *player)
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
			carr->op->f(vm, carr, player);
		}
		if (carr->op->f != zjmp)
			carr_move(carr, skip_args(vm, carr, carr->op->args_number, 1));
	}
}
