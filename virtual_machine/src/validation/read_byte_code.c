/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_byte_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:20:43 by egiant            #+#    #+#             */
/*   Updated: 2019/11/28 14:42:33 by hfrankly         ###   ########.fr       */
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
	header = buff[3]|(buff[2] << 8)|(buff[1] << 16)|(buff[0] << 24);
	if (header != COREWAR_EXEC_MAGIC)
		terminate_with_error(vm);
	//else
	//	printf("it's a success\n"); //для проверки, потом удалить
}

void			read_champion_name(t_corewar *vm, t_core *player, int fd)
{
	char		buff[PROG_NAME_LENGTH];
	int			ret;

	ret = read(fd, player->name, PROG_NAME_LENGTH);
	if (ret < 0)
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
	//else
	//	ft_printf("%x!\n", buff); //для проверки, потом удалить
}

void			read_exec_code_size(t_corewar *vm, t_core *player, int fd)
{
	uint32_t	rev_buff;
	uint8_t		buff[4];
	char		*code_size;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret < 0)
		terminate_with_error(vm);
	player->exec_code_size = buff[3]|(buff[2] << 8)|(buff[1] << 16)|(buff[0] << 24);
}

void			read_champion_comment(t_corewar *vm, t_core *player, int fd)
{
	char		buff[COMMENT_LENGTH];
	int			ret;

	ret = read(fd, &buff, COMMENT_LENGTH);
	if (ret < 0)
		ft_printf("error\n");
	ft_strcpy(player->comment, buff);
	//ft_printf("%s\n", buff);
}

void 			read_exec_code(t_corewar *vm, t_core *player, int fd)
{
	char		c;
	uint16_t	i;

	i = 0;
	while (read(fd, &c, 1) && i < player->exec_code_size)
	{
		player->exec_code[i] = c;
		i++;
	}
}

void			read_byte_code(t_corewar **vm)
{
	int 		n;
	int			fd;

	n = 0;
	while ((*vm)->cores[n])
	{
		fd = open((*vm)->cores[n]->file_path, O_RDONLY);
		read_magic_header((*vm), fd);
		read_champion_name((*vm), (*vm)->cores[n], fd);
		read_null_octet((*vm), fd);
		read_exec_code_size((*vm), (*vm)->cores[n], fd);
		read_champion_comment((*vm), (*vm)->cores[n], fd);
		read_null_octet((*vm), fd);
		read_exec_code((*vm), (*vm)->cores[n], fd);
		(*vm)->cores[n]->color = (n + 1) * 0xFFAAEE;
		++n;
	}
}