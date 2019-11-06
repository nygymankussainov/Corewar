/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:56:47 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/06 21:57:15 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_tokens(t_token *token, t_major *major)
{
	t_token	*head;

	head = token;
	while (token)
	{
		major->col = token->col;
		major->row = token->row;
		if (token->type == Operation)
			token = validate_args(token, major);
		else
			token = token->next;
	}
	// validate_labels(head);
}
