/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 17:49:05 by vhazelnu         ###   ########.fr       */
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

	i = COL;
	while ((*line)[COL] && !iswhitesp((*line)[COL]) &&
	(*line)[COL] != DIRECT_CHAR)
		COL++;
	(*token)->last->name = ft_strsub(*line, i, COL - i);
	COL = ft_skip_whitesp(*line, COL);
	if (!(*line)[COL])
		print_error(line, Syntax, "Endline at ", major);
	if (find_operation((*token)->last->name) < 0)
		print_error(line, Syntax, "Invalid operation at ", major);
}

void	validate_dir_label(char **line, t_major *major, t_token **token)
{
	int		i;

	COL += 2;
	i = COL;
	while ((*line)[COL] && !iswhitesp((*line)[COL]) &&
	(*line)[COL] != SEPARATOR_CHAR)
		COL++;
	(*token)->last->name = ft_strsub(*line, i, COL - i);
}

void	validate_separator(char **line, t_major *major)
{
	COL = ft_skip_whitesp(*line, COL + 1);
	if (!(*line)[COL])
		print_error(line, Syntax, "No argument after separator at ", major);
}

t_token	*validation(char *file, t_major *major)
{
	char	*line;

	line = NULL;
	validate_file(file, major);
	if (!validate_name_and_comment(&line, major))
		return (NULL);
	ft_strdel(&line);
	get_next_line(FD, &line, 1);
	lseek(FD, 0, SEEK_SET);
	return (tokenization(&line, major));
}
