/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:03:33 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 11:36:24 by vhazelnu         ###   ########.fr       */
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
		major->col = ft_skip_whitesp(*line, major->col);
		if ((*line)[major->col] && (*line)[major->col] == DIRECT_CHAR)
		{
			if ((*line)[major->col + 1] == LABEL_CHAR)
				create_token(line, major, token, Dir_label);
			else
				create_token(line, major, token, Direct);
		}
		else if ((*line)[major->col] && (*line)[major->col] == LABEL_CHAR)
			create_token(line, major, token, Ind_label);
		else if ((*line)[major->col] && (*line)[major->col] == 'r')
			create_token(line, major, token, Register);
		else if ((*line)[major->col] && (*line)[major->col] == SEPARATOR_CHAR)
		{
			if (i == 2)
				print_error(line, Syntax, "Extra separator at ", major);
			create_token(line, major, token, Separator);
			i++;
		}
		else if ((*line)[major->col] &&
			((*line)[major->col] == '-' || ft_isdigit((*line)[major->col])))
			create_token(line, major, token, Indirect);
		else if ((*line)[major->col])
		{
			major->col = ft_skip_whitesp(*line, major->col);
			if ((*line)[major->col] != COMMENT_CHAR &&
				(*line)[major->col] != ALT_COMMENT_CHAR)
				print_error(line, Syntax, "Invalid argument at ", major);
		}
	}
	if ((*line)[major->col - 1] != '\n')
		print_error(line, Syntax, "Missing line feed at ", major);
	create_token(line, major, token, Line_feed);
}
