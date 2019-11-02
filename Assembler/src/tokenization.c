/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:36:41 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/02 22:02:50 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_another_line(char **line, t_major *major)
{
	ft_strdel(line);
	get_next_line(major->fd, line, 0);
	major->col = 0;
	major->row++;
}

void	write_name_or_comment(char **line, t_major *major, int col)
{
	int		i;

	i = 0;
	while ((*line)[major->col] && (*line)[major->col] != '"')
		major->col++;
	major->col++;
	while (!line || !*line || (*line)[major->col] == '\0')
		get_another_line(line, major);
	while ((*line)[major->col] && (*line)[major->col] != '"')
	{
		if (col == 5 && i > PROG_NAME_LENGTH)
			print_error(line, Name, NULL, major);
		else if (col == 8 && i > COMMENT_LENGTH)
			print_error(line, Comment, NULL, major);
		if (col == 5)
			major->name[i] = (*line)[major->col];
		else if (col == 8)
			major->comment[i] = (*line)[major->col];
		i++;
		major->col++;
		while (!line || !*line || (*line)[major->col] == '\0')
			get_another_line(line, major);
	}
}

void	tokenization(char **line, t_major *major)
{
	major->col = 0;
	major->row = 1;
	while (get_next_line(major->fd, line, 0))
	{
		if (line && *line && (!ft_strncmp(*line, ".name", 5) ||
			!ft_strncmp(*line, ".comment", 8)))
		{
			major->col = !ft_strncmp(*line, ".name", 5) ? 5 : 8;
			write_name_or_comment(line, major, major->col);
		}
		ft_strdel(line);
		major->row++;
	}
}
