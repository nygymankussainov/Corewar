/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:36:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 18:03:04 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_structs(t_token *token, t_major *major)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		ft_strdel(&token->name);
		free(token);
		token = tmp;
	}
	token = NULL;
	free(major);
	major = NULL;
}
