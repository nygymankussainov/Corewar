/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:10:07 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 17:04:14 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_error(char **line, int type, char *message, t_major *major)
{
	if (type == Syntax)
		putstrerr("Syntax error. ");
	else if (type == Lexical)
		putstrerr("Lexical error. ");
	else if (type == Name)
	{
		putstrerr("Champion name is too long ");
		ft_printf("(Max length is %d) ", PROG_NAME_LENGTH);
	}
	else if (type == Comment)
	{
		putstrerr("Champion comment is too long ");
		ft_printf("(Max length is %d) ", COMMENT_LENGTH);
	}
	if (message)
		putstrerr(message);
	ft_printf("[%d:%d]\n", ROW, COL + 1);
	if (line)
		ft_strdel(line);
	get_next_line(major->fd, line, 1);
	exit(type);
}
