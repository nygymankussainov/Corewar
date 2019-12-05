/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:09:10 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 19:47:21 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void	error_with_file_name(char *name, int code)
{
	write(2, "Error: File ", 12);
	write(2, name, ft_strlen(name));
	if (code == 1)
		write(2, " has an invalid header\n", 23);
	if (code == 2)
		write(2, " has a code size that differ from what its header says\n",
					55);
	if (code == 3)
		write(2, " has no null octet\n", 19);
	if (code == 4)
		write(2, " has wrong code size\n", 21);
	exit(0);
}

void	invalid_file_name(char *name)
{
	write(2, "Can't read source file ", 23);
	write(2, name, ft_strlen(name));
	ft_putchar('\n');
	exit(0);
}

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
