/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:26:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/01 18:12:49 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_args_value(t_vm *vm, t_carr *carr, int arg_nb, int size)
{
	int		i;
	char	*value;
	int		skip;

	i = 0;
	skip = arg_nb ? skip_args(vm, carr, arg_nb, 0) : 0;
	if (!(value = (char *)ft_memalloc(sizeof(char) * size + 1)))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	while (i < size)
	{
		value[i] = vm->arena[(carr->pos + i + skip) % MEM_SIZE];
		++i;
	}
	value = size > 1 ? rev_bytes(value, size) : value;
	vm->args[arg_nb] = *((int *)value);
	ft_strdel(&value);
}

void	get_arg_types(t_vm *vm, t_carr *carr)
{
	vm->args_type[0] = (vm->arena[carr->pos] & 0b11000000) >> 6;
	vm->args_type[1] = (vm->arena[carr->pos] & 0b00110000) >> 4;
	vm->args_type[2] = (vm->arena[carr->pos] & 0b00001100) >> 2;
}

void	create_carriage(t_player *player, t_carr **carr, int pos)
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
	(*carr)->player_id = player->id;
	(*carr)->reg[0] = -player->id;
	carr_move(*carr, pos);
}

t_carr	*vm_init(t_player *player, t_vm *vm)
{
	int		i;
	int		step;
	t_carr	*carr;

	i = 0;
	step = MEM_SIZE / vm->pl_nb;
	carr = NULL;
	while (i < vm->pl_nb)
	{
		ft_memcpy(vm->arena + (i * step), player[i].bytecode, \
		player[i].code_size);
		create_carriage(&player[i], &carr, i * step);		
		++i;
	}
	return (carr);
}

void	virtual_machine(t_player *player, t_vm *vm)
{
	t_carr	*carr;

	carr = vm_init(player, vm);
	announce_players(player, vm->pl_nb);
	// int fd = open("test", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	// write(fd, vm->arena, MEM_SIZE);
	battle(carr, player, vm);
}
