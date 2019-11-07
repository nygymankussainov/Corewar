/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:36:26 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 14:52:08 by vhazelnu         ###   ########.fr       */
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
	int				bytes;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
}					t_major;

# define COL		major->col
# define ROW		major->row

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
	Direct,
	Operation,
	Indirect,
	Separator,
	Label,
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
	bool			label;
	int				row;
	int				col;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*last;
}					t_token;

typedef struct		s_label
{
	char			*name;
	int				bytes;
	struct s_label	*next;
}					t_label;


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
void				create_operation(char **line, t_major *major,
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
void				validate_tokens(t_token *token, t_major *major);
void				validate_register(char **line, t_major *major,
	t_token **token);
int					find_operation(char *name);
t_token				*validate_args(t_token *token, t_major *major);
void				validate_labels(t_token *token, t_major *major, t_label *label);
void				create_label_list(t_label **label, t_token *token, int bytes);

#endif
