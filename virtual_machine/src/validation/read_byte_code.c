/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_byte_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:20:43 by egiant            #+#    #+#             */
/*   Updated: 2019/11/02 12:55:36 by hfrankly         ###   ########.fr       */
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
	//ft_printf("%x\n", header);
	if (header != COREWAR_EXEC_MAGIC)
		terminate_with_error(vm);
	else
		printf("it's a success\n"); //для проверки, потом удалить
}

void			read_champion_name(t_corewar *vm, t_core *player, int fd)
{
	char		buff[PROG_NAME_LENGTH];
	int			ret;

	ret = read(fd, &buff, PROG_NAME_LENGTH);
	if (ret < 0)
		terminate_with_error(vm);
	//if (ft_strcmp(player->name, buff) != 0)
	//	terminate_with_error(vm);
	ft_printf("%s\n", buff); //для проверки, потом удалить
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
	else
		ft_printf("%x!\n", buff); //для проверки, потом удалить
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
	rev_buff = buff[3]|(buff[2] << 8)|(buff[1] << 16)|(buff[0] << 24);
	code_size = ft_change_system_over_ten(rev_buff, 16, 0);
	ft_printf("%d\n", ft_atoi(code_size));
	if (ft_atoi(code_size) > CHAMP_MAX_SIZE || ft_atoi(code_size) <= 0)
		terminate_with_error(vm);
	player->exec_code_size = ft_atoi(code_size);
}

void			read_champion_comment(t_corewar *vm, t_core *player, int fd)
{
	char		buff[COMMENT_LENGTH];
	int			ret;

	ret = read(fd, &buff, COMMENT_LENGTH);
	if (ret < 0)
		ft_printf("error\n");
	ft_strcpy(player->comment, buff);
	ft_printf("%s\n", buff);
}

void 			read_exec_code(t_corewar *vm, t_core *player, int fd)
{
	int			ret;
	uint8_t		check;

	ret = read(fd, player->exec_code, player->exec_code_size);
	if (ret < 0)
		terminate_with_error(vm);
	//дальше read возвращает 1, как проверить что код чемпиона кончился?
	

}

void			read_byte_code(t_corewar *vm)
{
	int 		n;
	int			fd;
	char		*file_name;

	n = 0;
	while (vm->cores[n])
	{
		file_name = ft_strjoin(vm->cores[n]->name, ".cor", 0, 0);
		fd = open(file_name, O_RDONLY);
		read_magic_header(vm, fd);
		read_champion_name(vm, vm->cores[n], fd);
		read_null_octet(vm, fd);
		read_exec_code_size(vm, vm->cores[n], fd);
		read_champion_comment(vm, vm->cores[n], fd);
		read_null_octet(vm, fd);
		read_exec_code(vm, vm->cores[n], fd);
		free(file_name);
		++n;
	}
}