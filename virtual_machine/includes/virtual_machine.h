/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:29:38 by hfrankly          #+#    #+#             */
/*   Updated: 2019/10/30 19:59:16 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H

#include <stdint.h>
#include <stdbool.h>
#include "op.h"

typedef struct s_corewar	t_corewar;
typedef struct s_core		t_core;
typedef struct s_carriage	t_carriage;

struct t_corewar {
	t_core		*cores;
	uint8_t		arena[MEM_SIZE];
	t_carriage	*start_carriage;
	uint8_t		winner_id;
	uint32_t	total_cycles;
	uint32_t	current_cycles;
	uint32_t	cycles_to_die;
	uint32_t	check_count;
};

struct t_core {
	uint8_t		id;
	char		name[PROG_NAME_LENGTH];
	char		comment[COMMENT_LENGTH];
	uint16_t	exec_code_size;
	uint8_t		exec_code[CHAMP_MAX_SIZE];
};

struct t_carriage {
	uint8_t		id;
	bool		carry;
	uint8_t		operation;
	uint32_t	cycle_was_live;
	uint32_t	cycles_before_operation;
	uint32_t	current_position;
	uint32_t	offset_next_operation;
	int8_t		registers[REG_NUMBER];
};

#endif

