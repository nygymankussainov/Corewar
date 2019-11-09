/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:38 by hfrankly          #+#    #+#             */
/*   Updated: 2019/11/06 15:18:51 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#include "libft.h"
#include "ft_printf.h"

#include "op.h"
#include "operations.h"


typedef struct s_corewar		t_corewar;
typedef struct s_core			t_core;
typedef struct s_carriage		t_carriage;

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
	t_core			*player;
	int32_t			registers[REG_NUMBER];
	uint8_t			position;
	uint32_t		cycle_was_live;
	uint32_t		cycles_before_operation;
	uint32_t		offset_next_operation;
	t_carriage		*next;
}					t_carriage;

/*
// initialization
*/
t_corewar			*init_vm(void);
void				init_arena(t_corewar *vm);
void				init_core(t_core *player);
t_carriage			*init_carriage(t_corewar *vm, t_core *player);

void				set_exec_code(uint8_t *arena, uint16_t position, t_core *core);
void				set_carriages(t_corewar *vm, uint16_t position_step);

/*
// parsing
*/
void				parse_arguments(t_corewar *vm, int argc, char *argv[]);

/*
// validation
*/
void				read_byte_code(t_corewar *vm);

void				terminate_with_error(t_corewar *vm);
void				termination_with_error(char *error_string);
void				termination_with_perror(char *error_string, int code);

/*
// war
*/
void				start_war(t_corewar *vm);

#endif

