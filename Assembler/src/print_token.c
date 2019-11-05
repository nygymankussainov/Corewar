/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 22:04:02 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 22:15:07 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->name)
			ft_printf("%s", token->name);
		if (token->type == Operation || 
			token->type == Label)
			ft_printf(" ");
		else if (token->type == Separator)
			ft_printf(", ");
		else if (token->type == Line_feed)
			ft_printf("\n");
		if (token->type == Register)
			ft_printf("r%d", token->value);
		else if (token->type == Direct)
			ft_printf("%%%d", token->value);
		else if (token->type == Indirect)
			ft_printf("%d", token->value);
		token = token->next;
	}
}
