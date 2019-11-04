/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:01:10 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/04 20:53:59 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token	*check_line(char **line, t_major *major)
{
	t_token	*token;

	token = NULL;
	major->col = ft_skip_whitesp(*line, major->col);
	if ((*line)[major->col] == COMMENT_CHAR)
		return (token);
	else if (major->col > 0 && (*line)[major->col] == LABEL_CHAR && 
		(*line)[major->col - 1] != DIRECT_CHAR)
		create_token(*line, major, &token, Label);
	else
		find_op_on_line(*line, major, token);
	return (token);
}
