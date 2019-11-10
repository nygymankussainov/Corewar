/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:41:35 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 14:57:06 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		count_bytes(t_token *token, int i)
{
	int		bytes;

	bytes = 0;
	if (token->type == Register)
		bytes += 1;
	else if (token->type == Indirect)
		bytes += IND_SIZE;
	else if (token->type == Direct)
		bytes += g_ops[i].t_dir_size;
	return (bytes);
}

int		is_arg(t_token *token, int i)
{
	if (token->type == Indirect || token->type == Direct
		|| token->type == Dir_label || token->type == Ind_label
		|| token->type == Register)
	{
		if (token->type == Dir_label)
		{
			token->type = Direct;
			token->label = 1;
		}
		else if (token->type == Ind_label)
		{
			token->type = Indirect;
			token->label = 1;
		}
		return (count_bytes(token, i));
	}
	return (0);
}

t_token	*validate_args(t_token *token, t_major *major)
{
	int		count;
	int		i;
	int		bytes;

	i = find_operation(token->name);
	token->index = i;
	count = 0;
	token->bytes = major->bytes;
	bytes = 0;
	while (token && token->type != Line_feed)
	{
		if (token->type != Separator && (bytes += is_arg(token, i)))
		{
			COL = token->col;
			ROW = token->row;
			if (!(token->type & g_ops[i].args_type[count]))
				print_error(NULL, Syntax, "Invalid argument at ", major);
			if (token->next->type != Line_feed && token->next->type != Separator)
				print_error(NULL, Syntax, "Missing separator at ", major);
			count++;
		}
		token = token->next;
	}
	if (count != g_ops[i].args_number)
		print_error(NULL, Syntax, "Invalid number of arguments ", major);
	major->bytes += g_ops[i].args_type_code + bytes + 1;
	// if (major->bytes > CHAMP_MAX_SIZE)
	// 	print_error(NULL, Syntax, "Your champion is overweighted ", major);
	return (token);
}
