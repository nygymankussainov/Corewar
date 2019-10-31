/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:41:19 by egiant            #+#    #+#             */
/*   Updated: 2019/10/30 17:50:42 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

#define B_SIZE 4

void		get_players(t_vm *vm, int argc, char **data)
{
	short	n;
	char	**name;

	n = 0;
	while (++n < argc)
	{
		if (ft_strcmp(data[n], "-n") == 0)	
		{
			if (!data[n + 1])
				return ;
			name = ft_strsplit(data[n + 2], '.');
			vm->players[ft_atoi(data[n + 1]) - 1] = (t_player *)malloc(sizeof(t_player));
			vm->players[ft_atoi(data[n + 1]) - 1]->name = ft_strdup(name[0]);
			n += 2;
		}
	}
	n = 0;
	int i = 0;
	while (++n < argc)
	{
		if (ft_strcmp(data[n], "-n") == 0)
			n += 3;
		if (data[n])
		{
			name = ft_strsplit(data[n], '.');
			while (vm->players[i] != NULL)
				++i;
			vm->players[i] = (t_player *)malloc(sizeof(t_player));
			vm->players[i]->name = ft_strdup(name[0]);
		}
	}
}

void read_magic_header(char *player_name)
{
	int		fd;
	char	*file_name;
	uint8_t	buff[4];
	uint32_t header;

	file_name = ft_strjoin(player_name, ".cor");
	fd = open(file_name, O_RDONLY);
	int r = read(fd, &buff, 4);

	header = *(uint32_t*)buff;
	ft_printf("%x", buff[0]);
	ft_printf("%x", buff[1]);
	ft_printf("%x", buff[2]);
	ft_printf("%x", buff[3]);
	ft_printf("%x\n", header);
	header = buff[3]|(buff[2] << 8)|(buff[1] << 16)|(buff[0] << 24);
	ft_printf("%x\n", header);
	if (header == COREWAR_EXEC_MAGIC)
		printf("it's a success\n");
}

void read_byte_code(t_vm *vm)
{
	int n;

	n = 0;
	//while (vm->players[n])
	//{
		read_magic_header(vm->players[n]->name);
	//}
}

int			main(int argc, char *argv[])
{
	t_vm	*vm;

	//if (argc > 2)
	//{
		vm = init_vm();
		get_players(vm, argc, argv);
		read_byte_code(vm);
	/*}
	else
	{
		return (0);
		//нет аргументов или один аргумент
	}*/
	return (0);
}