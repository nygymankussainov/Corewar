/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:05:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 18:32:30 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		count_digit(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (line[i] == '-')
		i++;
	while (line[i] && ft_isdigit(line[i]))
	{
		i++;
		count++;
	}
	return (count);
}

int		skip_zeros(char *line, int i)
{
	if (line[i] == '-')
		i++;
	while (line[i] && line[i] == '0')
		i++;
	if (!line[i] || !ft_isdigit(line[i]))
		return (i - 1);
	return (i);
}

void	validate_register(char **line, t_major *major, t_token **token)
{
	int		i;

	i = ++COL;
	if (count_digit(*line + i) > 2)
		print_error(line, Syntax, "Too many digits for T_REG at ", major);
	if ((*line)[COL] == '-')
		COL++;
	while ((*line)[COL] && ft_isdigit((*line)[COL]))
		COL++;
	COL = ft_skip_whitesp(*line, COL);
	if ((*line)[COL] && (*line)[COL] != SEPARATOR_CHAR &&
		(*line)[COL] != COMMENT_CHAR && (*line)[COL] != ALT_COMMENT_CHAR)
		print_error(line, Syntax, "Argument T_REG is not well formated at ", major);
	i = skip_zeros(*line, i);
	(*token)->last->value = ft_atoi(*line + i);
	// if ((*token)->last->value > REG_NUMBER)
	// 	print_error(line, Syntax, "Register overflow at ", major);
}

void	validate_number(char **line, t_major *major, t_token **token, char c)
{
	int		i;
	int		sign;

	if (c != 'i')
		i = ++COL;
	else
		i = COL;
	sign = (*line)[COL] == '-' ? -1 : 1;
	if ((*line)[COL] == '-')
		COL++;
	if (!ft_isdigit((*line)[COL]))
		print_error(line, Lexical, "Argument is not digit at ", major);
	while ((*line)[COL] && ft_isdigit((*line)[COL]))
		COL++;
	COL = ft_skip_whitesp(*line, COL);
	if ((*line)[COL] && (*line)[COL] != SEPARATOR_CHAR &&
		(*line)[COL] != COMMENT_CHAR && (*line)[COL] != ALT_COMMENT_CHAR)
	{
		if (c == 'd')
			print_error(line, Syntax, "Missing separator at ", major);
		else
			print_error(line, Syntax, "Missing separator at ", major);
	}
	i = skip_zeros(*line, i);
	(*token)->last->value = ft_atoi(*line + i);
	(*token)->last->value *= sign;
}
