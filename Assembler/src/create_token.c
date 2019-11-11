/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:09:09 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 18:03:31 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_data_in_token(char **line, t_major *major,
	t_token **token, int type)
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
		validate_register(line, major, token);
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
	new->col = COL;
	new->row = ROW;
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
