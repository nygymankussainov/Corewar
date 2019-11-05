/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:01:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 18:08:53 by vhazelnu         ###   ########.fr       */
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

t_token	*check_line(char **line, t_major *major)
{
	t_token	*token;

	token = NULL;
	major->col = ft_skip_whitesp(*line, major->col);
	if ((*line)[major->col] == COMMENT_CHAR)
		return (token);
	else if ((major->col = islabel(*line)) > 0)
		create_token(line, major, &token, Label);
	else
	{
		major->col = ft_skip_whitesp(*line, major->col);
		find_op_on_line(line, major, &token);
	}
	return (token);
}
