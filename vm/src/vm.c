/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:26:22 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 15:07:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_init(t_player *player, t_major *major)
{
	int		i;
	int		j;
	int		k;
	int		step;

	j = 0;
	i = major->pl_nb;
	step = MEM_SIZE / major->pl_nb;
	major->arena[MEM_SIZE] = '\0';
	while (i--)
	{
		k = 0;
		while (k < player[i].code_size)
		{
			major->arena[j] = player[i].bytecode[k];
			++j;
			++k;
		}
		j = (major->pl_nb - i) * step;
	}
}

void	vm(t_player *player, t_major *major)
{
	vm_init(player, major);
	int fd = open("test", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	write(fd, major->arena, MEM_SIZE);
}
