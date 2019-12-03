/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:01:09 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 13:21:50 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "operations.h"
# include "ft_printf.h"

typedef enum		e_type
{
	Magic_header = 1,
	Name,
	Champ_code_size,
	Comment,
	End,
	Bytecode
}					t_type;

int					isplayer(char *str);
t_player			*validation(int argc, char **argv, int nb);
int					check_bytecode(char *argv, t_player *player, int nb, int j);
char				*rev_bytes(char *str, int size);
char				*read_from_fd(int fd, int size, int type, char *argv);
void				modify_players_id(t_player *player, char **argv, int argc, int nb);
void				delete_player(t_player *player, int nb);
void				virtual_machine(t_vm *vm);
void				announce_players(t_player *player, int nb);
void				battle(t_carr *carr, t_vm *vm);
void				set_opcode(t_vm *vm, t_carr *carr);
void				set_opcode(t_vm *vm, t_carr *carr);
void				verify_operation(t_vm *vm, t_carr *carr);
void				carr_move(t_carr *carr, int step);
int					skip_args(t_vm *vm, t_carr *carr, int arg_nb, bool del_arg);
void				get_arg_types(t_vm *vm, t_carr *carr);
void				get_args_value(t_vm *vm, t_carr *carr, int i, int size);
int					verify_args(t_vm *vm, t_carr *carr);
int					get_arg_size(t_carr *carr, int i);
int					check_arg(t_vm *vm, t_carr *carr, int i, int size);
int					check_reg(t_vm *vm, t_carr *carr, int size);
void				ft_itoh_vm(int32_t value, int size, t_vm *vm, int pos);
int					get_ind_value(t_vm *vm, t_carr *carr, int pos, int size);
void				create_carriage(t_carr **carr);

#endif
