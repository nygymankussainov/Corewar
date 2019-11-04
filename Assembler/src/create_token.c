/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:09:09 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/04 20:49:13 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	find_op_on_line(char *line, t_major *major, t_token **token)
{
	int		i;

	i = 3;
	while (line[major->col])
	{
		if ((line[major->col] != COMMENT_CHAR || line[major->col] != ALT_COMMENT_CHAR)
			&& ft_isascii(line[major->col]))
		{
			create_token(line, major, token, Operation);
			while (i--)
			{
				major->col = ft_skip_whitesp(line, major->col);
				if (line[major->col] && line[major->col] == DIRECT_CHAR)
				{
					if (line[major->col + 1] == LABEL_CHAR)
						create_token(line, major, token, Dir_label);
					else
						create_token(line, major, token, Direct);
				}
				else if (line[major->col] && line[major->col] == LABEL_CHAR)
					create_token(line, major, token, Ind_label);
				else if (line[major->col] && line[major->col] == 'r')
					create_token(line, major, token, Register);
				else if (line[major->col] && line[major->col] == SEPARATOR_CHAR)
				{
					if (i == 2)
						print_error(*line, Syntax, "Extra separator at ", major);
					create_token(line, major, token, Separator);
					i++;
				}
				else if (line[major->col] && ft_isdigit(line[major->col]))
				{
					while (line[major->col] && (!iswhitesp(line[major->col]) ||
						line[major->col] != SEPARATOR_CHAR))
					{
						if (line[major->col] != SEPARATOR_CHAR && !iswhitesp(line[major->col])
							&& !ft_isdigit(line[major->col]))
							print_error(*line, Syntax, "Invalid symbol at ", major);
						major->col++;
					}
					create_token(line, major, token, Indirect);
				}
				else
					print_error(*line, Syntax, "Invalid argument at ", major);
			}
			return ;
		}
		major->col++;
	}
}

void	write_data_in_token(char *line, t_major *major, t_token **token, int type)
{
	int		i;

	i = major->col;
	if (type == Label)
	{
		while (i > 0 && line[i] && !iswhitesp(line[i]))
			i--;
		(*token)->last->name = ft_strsub(line, i, major->col + 1);
		major->col = ft_skip_whitesp(line, ++major->col);
		find_op_on_line(line, major, token);
	}
	else if (type == Operation)
	{
		while (line[major->col] && (!iswhitesp(line[major->col]) ||
		line[major->col] != DIRECT_CHAR || line[major->col] != LABEL_CHAR))
			major->col++;
		(*token)->last->name = ft_strsub(line, i, major->col + 1);
	}
	else if (type == Dir_label)
	{
		while (line[major->col])
	}
	(*token)->last->type = type;
}

void	create_token(char *line, t_major *major, t_token **token, int type)
{
	t_token	*new;

	if (!(new = (t_token *)ft_memalloc(sizeof(t_token))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (!*token)
	{
		*token = new;
		(*token)->last = *token;
	}
	else
	{
		new->prev = (*token)->last;
		(*token)->last->next = new;
		(*token)->last = new;
	}
	write_data_in_token(line, major, token, type);
}
