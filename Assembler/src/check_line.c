/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:01:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 21:22:43 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		islabel(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (i > 0 && line[i] == LABEL_CHAR &&
			line[i - 1] != DIRECT_CHAR)
			return (i);
		i++;
	}
	return (0);
}

void	check_line(char **line, t_major *major, t_token **token)
{
	int		tmp;

	major->col = ft_skip_whitesp(*line, major->col);
	if ((*line)[major->col] == COMMENT_CHAR)
		return ;
	else if ((tmp = islabel(*line)) > 0)
	{
		major->col = tmp;
		create_token(line, major, token, Label);
	}
	else
		find_op_on_line(line, major, token);
}
