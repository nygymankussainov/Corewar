/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:26:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/04 13:55:53 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_args_value(t_vm *vm, t_carr *carr, int arg_nb, int size)
{
	int		i;
	char	*value;
	int		skip;

	skip = arg_nb ? skip_args(vm, carr, arg_nb, 0) : 0;
	if (size > 1)
	{
		if (!(value = (char *)ft_memalloc(sizeof(char) * size + 1)))
		{
			ft_printf("%s\n", strerror(12));
			exit(12);
		}
		i = 0;
		while (i < size)
		{
			value[i] = vm->arena[(carr->pos + i + skip) % MEM_SIZE];
			++i;
		}
		value = rev_bytes(value, size);
		vm->args[arg_nb] = (size == 2) ? *((short *)value) : *((int *)value);
		ft_strdel(&value);
	}
	else
		vm->args[arg_nb] = (int)vm->arena[(carr->pos + skip) % MEM_SIZE];
}

void	get_arg_types(t_vm *vm, t_carr *carr)
{
	vm->args_type[0] = (vm->arena[carr->pos] & 0b11000000) >> 6;
	vm->args_type[1] = (vm->arena[carr->pos] & 0b00110000) >> 4;
	vm->args_type[2] = (vm->arena[carr->pos] & 0b00001100) >> 2;
}

void	create_carriage(t_carr **carr)
{
	t_carr	*new;

	if (!(new = (t_carr *)ft_memalloc(sizeof(t_carr))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (!*carr)
	{
		*carr = new;
		(*carr)->id = 1;
	}
	else
	{
		new->next = *carr;
		(*carr)->prev = new;
		*carr = new;
		(*carr)->id = (*carr)->next->id + 1;
	}
}

t_carr	*craete_arena(t_vm *vm)
{
	int		i;
	int		step;
	t_carr	*carr;

	i = 0;
	step = MEM_SIZE / vm->pl_nb;
	carr = NULL;
	while (i < vm->pl_nb)
	{
		ft_memcpy(vm->arena + (i * step), vm->player[i].bytecode, \
		vm->player[i].code_size);
		create_carriage(&carr);	
		carr->player_id = vm->player[i].id;
		carr->reg[0] = -vm->player[i].id;
		carr_move(carr, i * step);
		vm->head = carr;
		++i;
	}
	return (carr);
}

void	virtual_machine(t_vm *vm)
{
	t_carr	*carr;

	carr = craete_arena(vm);
	announce_players(vm->player, vm->pl_nb);
	battle(carr, vm);
	int fd = open("test", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	write(fd, vm->arena, MEM_SIZE);
}
