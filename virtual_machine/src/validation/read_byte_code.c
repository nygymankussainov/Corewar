/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_byte_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:20:43 by egiant            #+#    #+#             */
/*   Updated: 2019/12/02 13:31:37 by egiant           ###   ########.fr       */
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
}

int			read_champion_name(t_corewar *vm, t_core *player, int fd)
{
	char		buff[PROG_NAME_LENGTH];
	int			ret;
	t_core		*core;
	int 		number;

	number = 0;
	ret = read(fd, &buff, PROG_NAME_LENGTH);
	if (ret < 0)
		terminate_with_error(vm);
	if (player->id != 0)
		number = player->id - 1;
	else {
		while (vm->cores[number])
			number++;
	}
	if (vm->cores[number] || number > 3)
		terminate_with_error(vm);
	vm->cores[number] = (t_core*)malloc(sizeof(t_core));
	core = vm->cores[number];
	init_core(core);
	core->id = number + 1;
	ft_strcpy(core->name, buff);
	return (number);
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

void			read_exec_code_size(t_corewar *vm, t_core *core, int fd)
{
	uint32_t	rev_buff;
	uint8_t		buff[4];
	char		*code_size;
	int			ret;

	ret = read(fd, &buff, 4);
	if (ret < 0)
		terminate_with_error(vm);
	core->exec_code_size = buff[3]|(buff[2] << 8)|(buff[1] << 16)|(buff[0] << 24);
	if (core->exec_code_size > CHAMP_MAX_SIZE)
		terminate_with_error(vm);
}

void			read_champion_comment(t_corewar *vm, t_core *core, int fd)
{
	char		buff[COMMENT_LENGTH];
	int			ret;

	ret = read(fd, &buff, COMMENT_LENGTH);
	if (ret < 0)
		terminate_with_error(vm);
	ft_strcpy(core->comment, buff);
}

void 			read_exec_code(t_corewar *vm, t_core *core, int fd)
{
	int			ret;
	char		c;
	uint16_t	i;

	i = 0;
	while (i < core->exec_code_size)
	{
		ret = read(fd, &c, 1);
		if (ret <= 0)
			terminate_with_error(vm);
		core->exec_code[i] = c;
		i++;
	}
	ret = read(fd, &c, 1);
	if (ret != 0)
		terminate_with_error(vm);
}

void check_cores(t_corewar *vm)
{
    int n;

    n = 0;
    while (vm->cores[n] && n < 4) //n < 4 added by screight
        ++n;
    if (n != vm->number_of_players)
        terminate_with_error(vm);
}

void			read_byte_code(t_corewar **vm)
{
	int 		id;
	int			fd;
	char		*file_name;
	t_core		*core_tmp;
	int			n;

	n = 0;
	core_tmp = (*vm)->line_of_players;
	while (core_tmp)
	{
		file_name = core_tmp->executable_file_name;
		fd = open(file_name, O_RDONLY);
		read_magic_header((*vm), fd);
		id = read_champion_name((*vm), core_tmp, fd);
		read_null_octet((*vm), fd);
		read_exec_code_size((*vm), (*vm)->cores[id], fd);
		read_champion_comment((*vm), (*vm)->cores[id], fd);
		read_null_octet((*vm), fd);
		read_exec_code((*vm), (*vm)->cores[id], fd);
		set_player_color((*vm), n);
		free(file_name);
		core_tmp = core_tmp->next;
		++n;
	}
	//free_list((*vm)->line_of_players);
	check_cores(*vm);
	(*vm)->winner = (*vm)->cores[(*vm)->number_of_players - 1];
}