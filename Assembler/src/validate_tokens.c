/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:56:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 14:51:48 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_tokens(t_token *token, t_major *major)
{
	t_token		*head;
	t_label		*label;


	head = token;
	label = NULL;
	while (token)
	{
		COL = token->col;
		ROW = token->row;
		if (token->type == Operation)
			token = validate_args(token, major);
		else if (token->type == Label)
			create_label_list(&label, token, major->bytes);
		token = token->next;
	}
	validate_labels(head, major, label);
}
