/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:03:33 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 18:35:46 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	create_operation(char **line, t_major *major, t_token **token)
{
	int		i;

	i = 3;
	create_token(line, major, token, Operation);
	while (i--)
	{
		COL = ft_skip_whitesp(*line, COL);
		if ((*line)[COL] && (*line)[COL] == DIRECT_CHAR)
		{
			if ((*line)[COL + 1] == LABEL_CHAR)
				create_token(line, major, token, Dir_label);
			else
				create_token(line, major, token, Direct);
		}
		else if ((*line)[COL] && (*line)[COL] == LABEL_CHAR)
			create_token(line, major, token, Ind_label);
		else if ((*line)[COL] && (*line)[COL] == 'r')
			create_token(line, major, token, Register);
		else if ((*line)[COL] && (*line)[COL] == SEPARATOR_CHAR)
		{
			if (i == 2)
				print_error(line, Syntax, "Extra separator at ", major);
			create_token(line, major, token, Separator);
			i++;
		}
		else if ((*line)[COL] &&
			((*line)[COL] == '-' || ft_isdigit((*line)[COL])))
			create_token(line, major, token, Indirect);
		else if ((*line)[COL])
		{
			COL = ft_skip_whitesp(*line, COL);
			if ((*line)[COL] != COMMENT_CHAR &&
				(*line)[COL] != ALT_COMMENT_CHAR)
				print_error(line, Syntax, "Invalid argument at ", major);
		}
	}
	COL = ft_skip_whitesp(*line, COL);
	if (((*line)[COL] && (*line)[COL] != '\n' && (*line)[COL] != COMMENT_CHAR &&
		(*line)[COL] != ALT_COMMENT_CHAR) || (!(*line)[COL] && (*line)[COL - 1] != '\n'))
		print_error(line, Syntax, "Missing line feed at ", major);
	create_token(line, major, token, Line_feed);
}
