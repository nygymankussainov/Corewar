/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:01:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 20:40:15 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		islabel(char *line)
{
	int		i;

	i = 0;
	while (line[i] && !iswhitesp(line[i]))
	{
		if (i > 0 && line[i] == LABEL_CHAR &&
			line[i - 1] != DIRECT_CHAR)
			return (i - 1);
		i++;
	}
	return (0);
}

void	check_line(char **line, t_major *major, t_token **token)
{
	int		tmp;

	COL = ft_skip_whitesp(*line, COL);
	if ((*line)[COL] == COMMENT_CHAR)
		return ;
	else if ((tmp = islabel((*line) + COL)) > 0)
	{
		COL = tmp + COL;
		create_token(line, major, token, Label);
	}
	else if ((*line)[COL] == COMMENT_CHAR ||
		(*line)[COL] == ALT_COMMENT_CHAR)
		ROW++;
	else if ((*line)[COL])
		create_operation(line, major, token);
}
