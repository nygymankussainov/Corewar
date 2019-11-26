/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:01:09 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/26 21:40:40 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"

typedef struct	s_player
{
	int			id;
	char		*name;
	char		*comment;
	int			code_size;
	char		*bytecode;
}				t_player;

typedef enum		e_type
{
	Magic_header = 1,
	Name,
	Champ_code_size,
	Comment,
	End,
	Bytecode
}					t_type;

int				isplayer(char *str);
int				validation(int argc, char **argv, int nb);
int				check_bytecode(char *argv, t_player *player, int nb, int j);
char			*rev_bytes(char *str, int size);
char			*read_from_fd(int fd, int size, int type, char *argv);
int				find_flag(t_player *player, char **argv, int argc, int nb);
void			delete_player(t_player *player, int nb);

#endif
