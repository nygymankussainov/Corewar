/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:09:10 by egiant            #+#    #+#             */
/*   Updated: 2019/11/02 14:30:35 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	terminate_with_error(t_corewar *vm)
{
    //free_corewar(vm);
	write(2, "Error\n", 6);
	exit (0);
}

void	termination_with_error(char *error_string)
{
	write(2, error_string, ft_strlen(error_string));
	exit (0);
}

void	termination_with_perror(char *error_string, int code)
{
	errno = code;
	//perror(error_string);
	exit(0);
}