/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_label_in_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:00:56 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 21:20:21 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_label_in_token(char **line, t_major *major, t_token **token, int type)
{
	int		i;

	i = major->col;
	while (i > 0 && (*line)[i] && !iswhitesp((*line)[i - 1]))
		i--;
	(*token)->last->name = ft_strsub(*line, i, major->col - i + 1);
	major->col = ft_skip_whitesp(*line, ++major->col);
	(*token)->last->type = type;
	find_op_on_line(line, major, token);
}

void	write_ind_label_in_token(char **line, t_major *major, t_token **token)
{
	int		i;

	i = major->col;
	while ((*line)[major->col] && !iswhitesp((*line)[major->col]) &&
	(*line)[major->col] != SEPARATOR_CHAR)
		major->col++;
	(*token)->last->name = ft_strsub(*line, i, major->col - i);
}
