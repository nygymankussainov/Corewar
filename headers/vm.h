/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:04:37 by egiant            #+#    #+#             */
/*   Updated: 2019/10/31 18:26:30 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
#define VM_H

# include "op.h"
# include "stdint.h"
# include "libftprintf.h"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct		s_player
{
	int				number;
	char			*name;
	char			*comment;
	int				exec_code_size;
	uint8_t			*exec_code;

	struct s_player *next;
}					t_player;

typedef struct		s_vm
{
	uint8_t			arena[MEM_SIZE];
	t_player		*players[MAX_PLAYERS];
	t_player		*line_of_players;
	int				number_of_players;
}					t_vm;


t_vm				*init_vm(void);
void				parse_arguments(t_vm *vm, int argc, char *argv[]);
void				init_player(t_player *player);
void				terminate_with_error(t_vm *vm);
void				read_byte_code(t_vm *vm);

#endif