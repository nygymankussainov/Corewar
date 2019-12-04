/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:01:05 by egiant            #+#    #+#             */
/*   Updated: 2019/12/04 18:08:59 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int				is_name(t_corewar *vm, char *str)
{
	char		*ptr;

	if (!(ptr = ft_strstr(str, ".cor")))
		terminate_with_error(vm);
	return (1);
}
