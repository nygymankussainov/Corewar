/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cores.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:56:40 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 18:39:36 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void		check_cores(t_corewar *vm)
{
	int		n;

	n = 0;
	while (vm->cores[n])
		++n;
	if (n != vm->number_of_players)
		termination_with_error("Wrong sequence of players\n");
}
