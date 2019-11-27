/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:35:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/27 16:53:00 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		check_exec_code(int fd, char *argv, t_player *player, int type)
{
	if (!(player->bytecode = read_from_fd(fd, player->code_size, type, argv)))
		return (0);
	return (1);
}

int		check_name_or_comment(int fd, char *argv, t_player *player, int type)
{
	char	*end;

	if (type == Name)
	{
		if (!(player->name = read_from_fd(fd, PROG_NAME_LENGTH, type, argv)))
			return (0);
	}
	else if (!(player->comment = read_from_fd(fd, COMMENT_LENGTH, Name, argv)))
		return (0);
	if (!(end = read_from_fd(fd, 4, End, argv)))
		return (0);
	if (*end)
	{
		putstrerr("Missing EOF in ");
		putstrerr(argv);
		putstrerr("\n");
		ft_strdel(&end);
		return (0);
	}
	ft_strdel(&end);
	return (1);
}

int		check_code_size(int fd, char *argv, t_player *player)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = read_from_fd(fd, 4, Champ_code_size, argv)))
		return (0);
	str = rev_bytes(str, 4);
	player->code_size = *((int*)str);
	ft_strdel(&str);
	if (player->code_size > CHAMP_MAX_SIZE)
	{
		putstrerr(argv);
		putstrerr(" is overweighted!\n");
		return (0);
	}
	return (1);
}

int		check_magic_header(int fd, char *argv)
{
	char	*str;
	char	*magic_header;

	if (!(str = read_from_fd(fd, 4, Magic_header, argv)))
		return (0);
	magic_header = rev_bytes(str, 4);
	if (*((int *)magic_header) != COREWAR_EXEC_MAGIC)
	{
		putstrerr("Missing magic header in ");
		putstrerr(argv);
		putstrerr("\n");
		ft_strdel(&str);
		return (0);
	}
	ft_strdel(&str);
	return (1);
}

int		check_bytecode(char *argv, t_player *player, int nb, int j)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror("");
		putstrerr(" ");
		putstrerr(argv);
		putstrerr("\n");
		delete_player(player, nb);
		return (0);
	}
	player += j;
	if (!check_magic_header(fd, argv) ||
		!check_name_or_comment(fd, argv, player, Name) ||
		!check_code_size(fd, argv, player) ||
		!check_name_or_comment(fd, argv, player, Comment) ||
		!check_exec_code(fd, argv, player, Bytecode))
	{
		player -= j;
		delete_player(player, nb);
		return (0);
	}
	player->id = j + 1;
	return (1);
}
