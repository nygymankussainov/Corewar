/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:38 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/01 16:33:49 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

#include <stdint.h>
#include <stdbool.h>
#include "op.h"
#include "libft.h"
#include "ft_printf.h"

typedef struct s_core {
	uint8_t			id;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	uint16_t		exec_code_size;
	uint8_t			exec_code[CHAMP_MAX_SIZE];
	struct s_core	*next;
}					t_core;

typedef struct 		s_carriage {
	uint8_t			id;
	bool			carry;
	uint8_t			operation;
	uint32_t		cycle_was_live;
	uint32_t		cycles_before_operation;
	uint32_t		current_position;
	uint32_t		offset_next_operation;
	int32_t			registers[REG_NUMBER];
}					t_carriage;

typedef struct 		s_corewar {
	t_core			*cores[MAX_PLAYERS];
	t_core			*line_of_players;
	short			number_of_players;
	uint8_t			arena[MEM_SIZE];
	t_carriage		*start_carriage;
	uint8_t			winner_id;
	uint32_t		total_cycles;
	uint32_t		current_cycles;
	uint32_t		cycles_to_die;
	uint32_t		check_count;
}					t_corewar;


t_corewar			*init_vm(void);
void				parse_arguments(t_corewar *vm, int argc, char *argv[]);
void				init_core(t_core *player);
void				terminate_with_error(t_corewar *vm);
void				read_byte_code(t_corewar *vm);

#endif

