/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:50:41 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/06 16:56:16 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

//создать папку с оперциями в src

void do_op(t_corewar *vm, t_carriage *carriage)
{

}

void start_war(t_corewar *vm)
{
	t_carriage *tmp;

	tmp = vm->start_carriage;
	while (tmp)
	{
		do_op(vm, tmp);
		tmp = tmp->next;
	}
}
