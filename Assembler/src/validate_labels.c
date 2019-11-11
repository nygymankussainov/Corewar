/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:48:18 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 17:48:23 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	create_label_list(t_label **label, t_token *token, int bytes)
{
	t_label		*new;

	if (!(new = (t_label *)ft_memalloc(sizeof(t_label))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (!*label)
		*label = new;
	else
	{
		new->next = *label;
		*label = new;
	}
	(*label)->name = token->name;
	(*label)->bytes = bytes;
}

void	find_label(t_token *token, t_label *label, t_major *major)
{
	t_token	*tmp;

	while (label)
	{
		if (!ft_strcmp(token->name, label->name))
		{
			tmp = token;
			while (tmp && tmp->type != Operation)
				tmp = tmp->prev;
			token->value = label->bytes - tmp->bytes;
			return ;
		}
		label = label->next;
	}
	COL = token->col;
	ROW = token->row;
	print_error(NULL, Syntax, "No such label at ", major);
}

void	validate_labels(t_token *token, t_major *major, t_label *label)
{
	while (token)
	{
		if (token->label == 1)
			find_label(token, label, major);
		token = token->next;
	}
}
