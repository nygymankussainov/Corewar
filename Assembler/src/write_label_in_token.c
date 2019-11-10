/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_label_in_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:00:56 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 18:38:32 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_label_in_token(char **line, t_major *major, t_token **token, int type)
{
	int		i;

	i = COL;
	while (i >= 0 && (*line)[i] && !iswhitesp((*line)[i]))
	{
		if (!ft_islower((*line)[i]) && !ft_isdigit((*line)[i]) && (*line)[i] != '_')
		{
			COL = i;
			print_error(line, Lexical, "Invalid symbol at ", major);
		}
		i--;
	}
	i = ft_skip_whitesp(*line, ++i);
	(*token)->last->name = ft_strsub(*line, i, COL - i + 1);
	COL++;
	COL = ft_skip_whitesp(*line, ++COL);
	(*token)->last->type = type;
	if ((*line)[COL] && (*line)[COL] != COMMENT_CHAR &&
		(*line)[COL] != ALT_COMMENT_CHAR && (*line)[COL] != LABEL_CHAR)
		create_operation(line, major, token);
}

void	write_ind_label_in_token(char **line, t_major *major, t_token **token)
{
	int		i;

	i = ++COL;
	while ((*line)[COL] && !iswhitesp((*line)[COL]) &&
	(*line)[COL] != SEPARATOR_CHAR)
	{
		if (!ft_islower((*line)[COL]) && !ft_isdigit((*line)[COL]) && (*line)[COL] != '_')
			print_error(line, Lexical, "Invalid symbol at ", major);
		COL++;
	}
	(*token)->last->name = ft_strsub(*line, i, COL - i);
}
