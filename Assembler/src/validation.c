/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/06 21:42:48 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		find_operation(char *name)
{
	int		i;

	i = 0;
	while (i < OP_NUMBER)
	{
		if (!ft_strcmp(g_ops[i].name, name))
			return (i);
		i++;
	}
	return (-1);
}

void	validate_operation(char **line, t_major *major, t_token **token)
{
	int		i;

	i = major->col;
	while ((*line)[major->col] && !iswhitesp((*line)[major->col]) &&
	(*line)[major->col] != DIRECT_CHAR)
		major->col++;
	(*token)->last->name = ft_strsub(*line, i, major->col - i);
	major->col = ft_skip_whitesp(*line, major->col);
	if (!(*line)[major->col])
		print_error(line, Syntax, "Endline at ", major);
	if (find_operation((*token)->last->name) < 0)
		print_error(line, Syntax, "Invalid operation at ", major);
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
	print_token(token);
	return (1);
}
