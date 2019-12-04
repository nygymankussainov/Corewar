/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cores.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:56:40 by egiant            #+#    #+#             */
/*   Updated: 2019/12/04 18:08:44 by egiant           ###   ########.fr       */
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
		terminate_with_error(vm);
}
