/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_p1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:43:01 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/04 18:48:58 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_ind_value(t_vm *vm, t_carr *carr, int pos, bool mod)
{
	char	*address;
	int		i;
	int		value;

	i = 0;
	if (mod)
		pos = pos % IDX_MOD;
	if (!(address = (char *)ft_memalloc(sizeof(char) * REG_SIZE + 1)))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	while (i < REG_SIZE)
	{
		address[i] = vm->arena[get_pos(carr->pos - carr->skip + pos + i)];
		++i;
	}
	address = rev_bytes(address, REG_SIZE);
	value = *((int *)address);
	ft_strdel(&address);
	return (value);
}

void	sti(t_vm *vm, t_carr *carr)
{
	int		pos;
	int		i;

	i = 1;
	pos = 0;
	while (i < carr->op->args_number)
	{
		if (vm->args_type[i] == REG_CODE)
			pos += carr->reg[vm->args[i] - 1];
		else if (vm->args_type[i] == DIR_CODE)
			pos += vm->args[i];
		else
			pos += get_ind_value(vm, carr, vm->args[i], 1);
		++i;
	}
	pos %= IDX_MOD;
	ft_itoh_vm(carr->reg[vm->args[0] - 1], REG_SIZE, vm, carr->pos - carr->skip + pos);
}

void	ldi(t_vm *vm, t_carr *carr)
{
	int		value;
	int		pos;
	int		i;

	i = 0;
	pos = 0;
	while (i < carr->op->args_number - 1)
	{
		if (vm->args_type[i] == REG_CODE)
			pos += carr->reg[vm->args[i] - 1];
		else if (vm->args_type[i] == DIR_CODE)
			pos += vm->args[i];
		else
			pos += get_ind_value(vm, carr, vm->args[i], 1);
		++i;
	}
	value = get_ind_value(vm, carr, pos, 1);
	carr->reg[vm->args[i] - 1] = value;
}

void	st(t_vm *vm, t_carr *carr)
{
	int		pos;

	if (vm->args_type[1] == REG_CODE)
		carr->reg[vm->args[1] - 1] = carr->reg[vm->args[0] - 1];
	else
	{
		pos = vm->args[1] % IDX_MOD;
		ft_itoh_vm(carr->reg[vm->args[0] - 1], REG_SIZE, vm, carr->pos - carr->skip + pos);
	}
}

void	ld(t_vm *vm, t_carr *carr)
{
	int		i;

	i = 0;
	if (vm->args_type[0] == IND_CODE)
		vm->args[0] = get_ind_value(vm, carr, vm->args[0], 1);
	carr->reg[vm->args[1] - 1] = vm->args[0];
	carr->carry = carr->reg[vm->args[1] - 1] == 0 ? 1 : 0;
}
