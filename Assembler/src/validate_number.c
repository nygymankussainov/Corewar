/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:05:28 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/06 18:53:27 by vhazelnu         ###   ########.fr       */
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

	i = ++major->col;
	if (count_digit(*line + i) > 2)
		print_error(line, Syntax, "Too many digits for T_REG at ", major);
	if ((*line)[major->col] == '-')
		major->col++;
	while ((*line)[major->col] && ft_isdigit((*line)[major->col]))
		major->col++;
	major->col = ft_skip_whitesp(*line, major->col);
	if ((*line)[major->col] && (*line)[major->col] != SEPARATOR_CHAR &&
		(*line)[major->col] != COMMENT_CHAR && (*line)[major->col] != ALT_COMMENT_CHAR)
		print_error(line, Syntax, "Argument T_REG is not well formated at ", major);
	i = skip_zeros(*line, i);
	(*token)->last->value = ft_atoi(*line + i);
}

void	validate_number(char **line, t_major *major, t_token **token, char c)
{
	int		i;
	int		sign;

	if (c != 'i')
		i = ++major->col;
	else
		i = major->col;
	sign = (*line)[major->col] == '-' ? -1 : 1;
	if ((*line)[major->col] == '-')
		major->col++;
	while ((*line)[major->col] && ft_isdigit((*line)[major->col]))
		major->col++;
	major->col = ft_skip_whitesp(*line, major->col);
	if ((*line)[major->col] && (*line)[major->col] != SEPARATOR_CHAR &&
		(*line)[major->col] != COMMENT_CHAR && (*line)[major->col] != ALT_COMMENT_CHAR)
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
