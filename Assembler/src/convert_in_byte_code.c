/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_in_byte_code.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:04:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/09 18:53:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	calculate_args_type_code(t_token *token, t_major *major, int arg_nbr)
{
	int		res;
	int		i;

	res = 0;
	i = 0;
	while (i < arg_nbr)
	{
		if (token->type == Register)
			res |= 1 << 2 * (3 - i++);
		else if (token->type == Direct)
			res |= 2 << 2 * (3 - i++);
		else if (token->type == Indirect)
			res |= 3 << 2 * (3 - i++);
		token = token->next;
	}
	ft_itoh(res, 1, major);
}

void	calculate_op_code(t_token *token, t_major *major)
{
	int		arg_nbr;
	int		i;
	int		tmp;
	int		sign;

	arg_nbr = g_ops[token->index].args_number;
	tmp = g_ops[token->index].t_dir_size;
	ft_itoh(g_ops[token->index].opcode, 1, major);
	if (g_ops[token->index].args_type_code)
		calculate_args_type_code(token, major, arg_nbr);
	i = 0;
	while (i < arg_nbr)
	{
		sign = token->value < 0 ? -1 : 0;
		token->value *= token->value < 0 ? -1 : 1;
		if (token->type == Register || token->type == Direct ||
			token->type == Indirect)
		{
			if (token->type == Register)
				ft_itoh(token->value, 1, major);
			else if (token->type == Direct)
			{
				token->value = tmp == T_DIR ?
					(int32_t)token->value : (int16_t)token->value;
				if (sign < 0)
					ft_itoh(token->value * (int64_t)sign, tmp, major);
				else
					ft_itoh(token->value, tmp, major);
			}
			else
			{
				token->value = (int16_t)token->value;
				if (sign < 0)
					ft_itoh(token->value * (int64_t)sign, T_IND, major);
				else
					ft_itoh(token->value, tmp, major);
			}
			i++;
		}
		token = token->next;
	}
}

void	convert_in_byte_code(t_token *token, t_major *major)
{
	COL = 0;
	FD = open(major->filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	ft_strdel(&major->filename);
	if (!(BYTECODE = (u_int8_t *)ft_memalloc(sizeof(u_int8_t) *
		(PROG_NAME_LENGTH + COMMENT_LENGTH + major->bytes + 16))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	ft_itoh(COREWAR_EXEC_MAGIC, 4, major);
	ft_memcpy(BYTECODE + COL, major->name, ft_strlen(major->name));
	COL += PROG_NAME_LENGTH + 4;
	ft_itoh(major->bytes, 4, major);
	ft_memcpy(BYTECODE + COL, major->comment, ft_strlen(major->comment));
	COL += COMMENT_LENGTH + 4;
	while (token)
	{
		if (token->type == Operation)
			calculate_op_code(token, major);
		token = token->next;
	}
	write(FD, BYTECODE, PROG_NAME_LENGTH + COMMENT_LENGTH + major->bytes + 16);
	free(BYTECODE);
	BYTECODE = NULL;
}
