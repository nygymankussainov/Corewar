/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_magic_header_and_null_octet.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:13:36 by egiant            #+#    #+#             */
/*   Updated: 2019/12/04 18:16:39 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

void			read_magic_header(t_corewar *vm, int fd)
{
	uint8_t		buff[4];
	uint32_t	header;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret < 0)
		terminate_with_error(vm);
	header = buff[3] | (buff[2] << 8) | (buff[1] << 16) | (buff[0] << 24);
	if (header != COREWAR_EXEC_MAGIC)
		terminate_with_error(vm);
}

void			read_null_octet(t_corewar *vm, int fd)
{
	uint32_t	buff;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret < 0)
		terminate_with_error(vm);
	if (buff != 0)
		terminate_with_error(vm);
}
