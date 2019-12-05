/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_byte_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:20:43 by egiant            #+#    #+#             */
/*   Updated: 2019/12/05 17:36:04 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "virtual_machine.h"

int				read_champion_name(t_corewar *vm, t_core *player, int fd)
{
	char		buff[PROG_NAME_LENGTH];
	int			ret;
	int			number;
	t_core		*core;

	number = 0;
	ret = read(fd, &buff, PROG_NAME_LENGTH);
	if (ret < 0)
		terminate_with_error();
	if (player->id != 0)
		number = player->id - 1;
	else
	{
		while (vm->cores[number])
			number++;
	}
	if (vm->cores[number] || number > 3)
		terminate_with_error();
	if (!(vm->cores[number] = (t_core*)malloc(sizeof(t_core))))
		termination_with_perror("Core malloc error", ENOMEM);
	core = vm->cores[number];
	init_core(core);
	core->id = number + 1;
	ft_strcpy(core->name, buff);
	return (number);
}

void			read_exec_code_size(t_core *core, int fd)
{
	uint8_t		buff[4];
	int64_t		code_size;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret < 0)
		terminate_with_error();
	code_size = buff[3] | (buff[2] << 8) | (buff[1] << 16) | (buff[0] << 24);
	if (code_size <= 0 || code_size > CHAMP_MAX_SIZE)
		terminate_with_error();
	core->exec_code_size = (uint16_t)code_size;
}

void			read_champion_comment(t_core *core, int fd)
{
	char		buff[COMMENT_LENGTH];
	int			ret;

	ret = read(fd, &buff, COMMENT_LENGTH);
	if (ret < 0)
		terminate_with_error();
	ft_strcpy(core->comment, buff);
}

void			read_exec_code(t_core *core, int fd)
{
	int			ret;
	char		c;
	uint16_t	i;

	i = 0;
	while (i < core->exec_code_size)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			terminate_with_error();
		core->exec_code[i] = c;
		i++;
	}
	ret = read(fd, &c, 1);
	if (ret != 0)
		terminate_with_error();
}

void			read_byte_code(t_corewar **vm)
{
	int			id;
	int			fd;
	char		*file_name;
	t_core		*core_tmp;

	core_tmp = (*vm)->line_of_players;
	while (core_tmp)
	{
		file_name = core_tmp->executable_file_name;
		fd = open(file_name, O_RDONLY);
		read_magic_header(fd);
		id = read_champion_name((*vm), core_tmp, fd);
		read_null_octet(fd);
		read_exec_code_size((*vm)->cores[id], fd);
		read_champion_comment((*vm)->cores[id], fd);
		read_null_octet(fd);
		read_exec_code((*vm)->cores[id], fd);
		set_player_color((*vm), id);
		free(file_name);
		core_tmp = core_tmp->next;
	}
	check_cores(*vm);
	(*vm)->winner = (*vm)->cores[(*vm)->number_of_players - 1];
}
