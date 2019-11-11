/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_into_bytecode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:04:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 19:09:24 by vhazelnu         ###   ########.fr       */
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

void	calc_opcode_for_dir_and_ind(t_token *token, t_major *major,
	int dir_size)
{
	if (token->type == Direct)
	{
		token->value = dir_size == DIR_SIZE ?
			(int32_t)token->value : (int16_t)token->value;
		if (token->sign < 0)
			ft_itoh(token->value * (int64_t)token->sign, dir_size, major);
		else
			ft_itoh(token->value, dir_size, major);
	}
	else
	{
		token->value = (int16_t)token->value;
		if (token->sign < 0)
			ft_itoh(token->value * (int64_t)token->sign, IND_SIZE, major);
		else
			ft_itoh(token->value, IND_SIZE, major);
	}
}

void	calculate_op_code(t_token *token, t_major *major)
{
	int		arg_nbr;
	int		i;
	int		dir_size;

	arg_nbr = g_ops[token->index].args_number;
	dir_size = g_ops[token->index].t_dir_size;
	ft_itoh(g_ops[token->index].opcode, 1, major);
	if (g_ops[token->index].args_type_code)
		calculate_args_type_code(token, major, arg_nbr);
	i = 0;
	while (i < arg_nbr)
	{
		if (token->type == Register || token->type == Direct ||
			token->type == Indirect)
		{
			if (token->type == Register)
				ft_itoh(token->value, 1, major);
			else
				calc_opcode_for_dir_and_ind(token, major, dir_size);
			i++;
		}
		token = token->next;
	}
}

void	compile_into_bytecode(t_token *token, t_major *major)
{
	COL = 0;
	FD = open(major->filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
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
	ft_printf("Writing output program to %s\n", major->filename);
	ft_strdel(&major->filename);
	free(BYTECODE);
	BYTECODE = NULL;
}
