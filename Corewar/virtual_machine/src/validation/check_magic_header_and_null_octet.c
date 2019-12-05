/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic_header_and_null_octet.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:13:36 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 21:32:31 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			read_magic_header(char *name, int fd)
{
	uint8_t		buff[4];
	uint32_t	header;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret <= 0)
		error_with_file_name(name, No_code);
	header = buff[3] | (buff[2] << 8) | (buff[1] << 16) | (buff[0] << 24);
	if (header != COREWAR_EXEC_MAGIC)
		error_with_file_name(name, Magic_header);
}

void			read_null_octet(char *name, int fd)
{
	uint32_t	buff;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret <= 0)
		termination_with_error("Error\n");
	if (buff != 0)
		error_with_file_name(name, Null_octet);
}
