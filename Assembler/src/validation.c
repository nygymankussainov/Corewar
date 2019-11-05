/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/05 13:57:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	validate_operation(char **line, t_major *major, t_token **token, int i)
{
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

void	validate_direct(char **line, t_major *major, t_token **token, int i)
{
	while ((*line)[major->col] && !iswhitesp((*line)[major->col]) &&
	(*line)[major->col] != SEPARATOR_CHAR)
	{
		if (ft_isascii((*line)[major->col]) && (*line)[major->col] != DIRECT_CHAR
			&& !ft_isdigit((*line)[major->col]))
			print_error(line, Syntax, "Invalid argument T_DIR at ", major);
		major->col++;
	}
	(*token)->last->direct = ft_atoi(*line + i + 1);
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
