/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:10:07 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/02 14:10:14 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_error(char **line, int type, char *message, t_major *major)
{
	if (type == Syntax)
		putstrerr("Syntax error. ");
	else if (type == Lexical)
		putstrerr("Lexical error. ");
	putstrerr(message);
	ft_printf("[%d:%d].\n", major->row, major->col);
	ft_strdel(line);
	exit(type);
}
