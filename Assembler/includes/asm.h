/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:36:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 22:09:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "stdbool.h"
# include "ft_printf.h"
# include "op.h"
# include "operations.h"

typedef struct		s_major
{
	int				fd;
	int				row;
	int				col;
	char			*file;
	bool			carry;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
}					t_major;

enum				e_err_type
{
	Syntax = 1,
	Lexical,
	Name,
	Comment
};

typedef enum		e_type
{
	Register = 1,
	Operation,
	Separator,
	Label,
	Indirect,
	Direct,
	Dir_label,
	Ind_label,
	Line_feed,
	End
}					t_type;

typedef struct		s_token
{
	char			*name;
	int				value;
	int				bytes;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*last;
}					t_token;

void				print_token(t_token *token);
int					print_error(char **line, int type,
	char *message, t_major *major);
int					validation(char *file, t_major *major);
int					validate_file(char *file);
int					validate_name_and_comment(char **line, t_major *major);
t_token				*tokenization(char **line, t_major *major);
void				create_token(char **line, t_major *major,
	t_token **token, int type);
void				check_line(char **line, t_major *major, t_token **token);
void				find_op_on_line(char **line, t_major *major,
	t_token **token);
void				validate_operation(char **line, t_major *major,
	t_token **token);
void	validate_number(char **line, t_major *major,
	t_token **token, char c);

void				write_label_in_token(char **line, t_major *major,
	t_token **token, int type);
void				validate_dir_label(char **line, t_major *major,
	t_token **token);
void				write_ind_label_in_token(char **line, t_major *major,
	t_token **token);
void				validate_separator(char **line, t_major *major);

#endif
