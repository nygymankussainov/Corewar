/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:09:10 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 14:55:03 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	print_usage_and_exit(void)
{
	ft_printf("Usage: ./corewar [-a] [-v] [-dump <num> -n <num>] "\
			"<champion.cor> <...>\n");
	ft_printf("    %-11s : Print output from \"aff\" (Default is off)\n", "-a");
	ft_printf("    %-11s : Dump memory (32 octets per line)"\
							" after <num> cycles and exit\n", "-dump <num>");
	ft_printf("    %-11s : Run visualizer\n", "-v");
	ft_printf("    %-11s : Set <num> of the next player\n", "-n    <num>");
	exit(0);
}

void	terminate_with_error(void)
{
	write(2, "Error\n", 6);
	exit(0);
}

void	termination_with_error(char *error_string)
{
	write(2, error_string, ft_strlen(error_string));
	exit(0);
}

void	termination_with_perror(char *error_string, int code)
{
	errno = code;
	perror(error_string);
	exit(0);
}
