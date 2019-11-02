/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:36:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/02 14:45:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "ft_printf.h"

typedef struct	s_major
{
	int			fd;
	int			row;
	int			col;
}				t_major;

enum			e_err_type
{
	Syntax = 1,
	Lexical
};

int				print_error(char **line, int type,
	char *message, t_major *major);
int				validation(char *file, t_major *major);
int				validate_file(char *file);
int				validate_name_and_comment(char **line, t_major *major);

#endif
