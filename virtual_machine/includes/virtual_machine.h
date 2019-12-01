/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:38 by hfrankly          #+#    #+#             */
/*   Updated: 2019/12/01 16:13:49 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "libft.h"
#include "libftprintf.h"
#include "op.h"
#include "operations.h"

typedef struct s_core			t_core;
typedef struct s_carriage		t_carriage;
typedef struct s_point			t_point;

typedef struct 		s_point {
	int32_t			color;
	uint8_t			value;
}					t_point;

typedef struct 		s_corewar {
	//t_sdl			*sdl;
	t_core			*cores[MAX_PLAYERS];
	t_core			*line_of_players;
	short			number_of_players;
	t_point			arena[MEM_SIZE];
	t_carriage		*start_carriage;
	t_core			*winner;
	int16_t			carriage_count;
	bool			visual;
	uint32_t		total_cycles;
	uint32_t		current_cycles;
	int32_t			cycles_to_die;
	int32_t			dumps;
	uint32_t		live_count;
	uint32_t		check_count;
}					t_corewar;

typedef struct s_core {
	uint8_t			id;
	char			*executable_file_name;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	uint16_t		exec_code_size;
	uint8_t			exec_code[CHAMP_MAX_SIZE];
	uint16_t		cycle_was_live; // added recently
	int32_t			color; // init in read_byte_code
	struct s_core	*next;
}					t_core;

typedef struct 		s_carriage {
	uint8_t			id;
	bool			carry;
	t_operation		*operation;
	t_core			*player;
	int32_t			registers[REG_NUMBER];
	uint16_t		position;
	uint32_t		cycle_was_live;
	uint32_t		cycles_before_operation;
	uint32_t		offset_next_operation;
	t_carriage		*next;
	uint16_t		last_operation[4];
	int32_t			color;
	uint8_t			*adress;
}					t_carriage;


void				display_array(t_point *array, uint16_t rows, uint16_t cols);
void				introduce_players(t_corewar *vm);
/*
// initialization
*/
t_corewar			*init_vm(void);
void				init_arena(t_corewar *vm);
void				init_core(t_core *player);
t_carriage			*init_carriage(t_corewar *vm, t_core *player);

void				set_exec_code(t_point *arena, uint16_t position, t_core *core);
void				set_carriages(t_corewar *vm, uint16_t position_step);

/*
// parsing
*/
void				parse_arguments(t_corewar **vm, int argc, char *argv[]);

/*
// validation
*/
void				read_byte_code(t_corewar **vm);

void				terminate_with_error(t_corewar *vm);
void				termination_with_error(char *error_string);
void				termination_with_perror(char *error_string, int code);

/*
// war
*/
void				start_war(t_corewar *vm);
void				check(t_corewar **vm);
void				execute_carriages(t_corewar **vm);
void				set_arg_code(t_corewar *vm, t_carriage *carriage, int8_t **arg_code);
bool				is_valid_format(t_corewar *vm, t_carriage *carriage, int8_t arg_code[4]);
void				pass_args_bits(t_corewar *vm, t_carriage *carriage, int8_t arg_code[4]);

void				kill_carriage(t_corewar **vm, t_carriage *to_delete);
t_carriage			*copy_carriage(t_corewar *vm, t_carriage *to_copy); // need to be done

/*
 *  free
 */
void    free_corewar(t_corewar *vm);

#endif

