/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:04:02 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 14:53:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->type == Operation)
			ft_printf("%s ", token->name);
		else if (token->type == Separator)
			ft_printf(", ");
		else if (token->type == Line_feed)
			ft_printf("\n");
		if (token->type == Register)
			ft_printf("r%d", token->value);
		if (token->type == Direct)
			ft_printf("%%%d", token->value);
		if (token->type == Indirect)
			ft_printf("%d", token->value);
		token = token->next;
	}
}
