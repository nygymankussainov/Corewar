/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 13:04:37 by egiant            #+#    #+#             */
/*   Updated: 2019/10/30 16:11:50 by egiant           ###   ########.fr       */
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
	char			*name;
	char			*comment;
	struct s_player	*next;
}					t_player;

typedef struct		s_vm
{
	uint8_t			arena[MEM_SIZE];
	t_player		*players[MAX_PLAYERS];
}					t_vm;


t_vm				*init_vm(void);
#endif