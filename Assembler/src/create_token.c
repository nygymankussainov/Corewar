/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:09:09 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 22:12:09 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	find_op_on_line(char **line, t_major *major, t_token **token)
{
	int		i;

	i = 3;
	if ((*line)[major->col] && (*line)[major->col] != COMMENT_CHAR &&
		(*line)[major->col] != ALT_COMMENT_CHAR)
	{
		create_token(line, major, token, Operation);
		while (i--)
		{
			major->col = ft_skip_whitesp(*line, major->col);
			if ((*line)[major->col] && (*line)[major->col] == DIRECT_CHAR)
			{
				if ((*line)[major->col + 1] == LABEL_CHAR)
					create_token(line, major, token, Dir_label);
				else
					create_token(line, major, token, Direct);
			}
			else if ((*line)[major->col] && (*line)[major->col] == LABEL_CHAR)
				create_token(line, major, token, Ind_label);
			else if ((*line)[major->col] && (*line)[major->col] == 'r')
				create_token(line, major, token, Register);
			else if ((*line)[major->col] && (*line)[major->col] == SEPARATOR_CHAR)
			{
				if (i == 2)
					print_error(line, Syntax, "Extra separator at ", major);
				create_token(line, major, token, Separator);
				i++;
			}
			else if ((*line)[major->col] && ft_isdigit((*line)[major->col]))
				create_token(line, major, token, Indirect);
			else if ((*line)[major->col])
			{
				major->col = ft_skip_whitesp(*line, major->col);
				if ((*line)[major->col] != COMMENT_CHAR &&
					(*line)[major->col] != ALT_COMMENT_CHAR)
					print_error(line, Syntax, "Invalid argument at ", major);
			}
		}
	}
	create_token(line, major, token, Line_feed);
}

void	write_data_in_token(char **line, t_major *major, t_token **token, int type)
{
	if (type == Label)
		write_label_in_token(line, major, token, type);
	else if (type == Ind_label)
		write_ind_label_in_token(line, major, token);
	else if (type == Dir_label)
		validate_dir_label(line, major, token);
	else if (type == Direct)
		validate_number(line, major, token, 'd');
	else if (type == Indirect)
		validate_number(line, major, token, 'i');
	else if (type == Register)
		validate_number(line, major, token, 'r');
	else if (type == Operation)
		validate_operation(line, major, token);
	else if (type == Separator)
		validate_separator(line, major);
	if (type != Label)
		(*token)->last->type = type;
}

void	create_token(char **line, t_major *major, t_token **token, int type)
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
