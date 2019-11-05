/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 21:20:01 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_operation(char **line, t_major *major, t_token **token)
{
	int		i;

	i = major->col;
	while ((*line)[major->col] && !iswhitesp((*line)[major->col]) &&
	(*line)[major->col] != DIRECT_CHAR)
		major->col++;
	if (!(*line)[major->col])
	{
		major->col = i;
		print_error(line, Syntax, "Missing separator at ", major);
	}
	(*token)->last->name = ft_strsub(*line, i, major->col - i);
}

void	validate_number(char **line, t_major *major, t_token **token, char c)
{
	int		i;

	if (c != 'i')
		i = ++major->col;
	else
		i = major->col;
	while ((*line)[major->col] && (*line)[major->col] != SEPARATOR_CHAR)
	{
		if ((*line)[major->col] != '-' &&
			ft_isascii((*line)[major->col]) && !ft_isdigit((*line)[major->col]))
		{
			if (c == 'd')
				print_error(line, Syntax, "Argument T_DIR is not well formated at ", major);
			else if (c == 'r')
				print_error(line, Syntax, "Argument T_REG is not well formated at ", major);
			else
				print_error(line, Syntax, "Argument T_IND is not well formated at ", major);
		}
		major->col++;
	}
	(*token)->last->value = ft_atoi(*line + i);
}

void	validate_dir_label(char **line, t_major *major, t_token **token)
{
	int		i;

	i = major->col;
	while ((*line)[major->col] && !iswhitesp((*line)[major->col]) &&
	(*line)[major->col] != SEPARATOR_CHAR)
		major->col++;
	(*token)->last->name = ft_strsub(*line, i, major->col - i);
}

void	validate_separator(char **line, t_major *major)
{
	major->col = ft_skip_whitesp(*line, major->col + 1);
	if (!(*line)[major->col])
		print_error(line, Syntax, "No argument after separator at ", major);
}

int		validation(char *file, t_major *major)
{
	char	*line;
	t_token	*token;

	line = NULL;
	if (!(major->fd = validate_file(file)) ||
		!validate_name_and_comment(&line, major))
		return (0);
	ft_strdel(&line);
	get_next_line(major->fd, &line, 1);
	lseek(major->fd, 0, SEEK_SET);
	token = tokenization(&line, major);
	return (1);
}
