/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 15:36:41 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/06 14:14:18 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_another_line(char **line, t_major *major)
{
	ft_strdel(line);
	get_next_line(major->fd, line, 0);
	COL = 0;
	ROW++;
}

void	write_name_or_comment(char **line, t_major *major, int col, int i)
{
	col == 5 ? ++major->name_count : ++major->comment_count;
	if (major->name_count > 1 || major->comment_count > 1)
		print_error(line, 0, "Second name or comment at ", major);
	while ((*line)[COL] && (*line)[COL] != '"')
		COL++;
	COL++;
	while (!line || !*line || (*line)[COL] == '\0')
		get_another_line(line, major);
	while ((*line)[COL] && (*line)[COL] != '"')
	{
		if (col == 5 && i >= PROG_NAME_LENGTH)
			print_error(line, Name, NULL, major);
		else if (col == 8 && i >= COMMENT_LENGTH)
			print_error(line, Comment, NULL, major);
		if (col < 8)
			major->name[i] = (*line)[COL];
		else if (col >= 8)
			major->comment[i] = (*line)[COL];
		i++;
		COL++;
		while (!line || !*line || (*line)[COL] == '\0')
			get_another_line(line, major);
	}
}

t_token	*tokenization(char **line, t_major *major)
{
	t_token	*token;

	ROW = 1;
	token = NULL;
	while (get_next_line(major->fd, line, 0) > 0)
	{
		COL = ft_skip_whitesp(*line, 0);
		if (line && *line && (!ft_strncmp(*line + COL, ".name", 5) ||
			!ft_strncmp(*line + COL, ".comment", 8)))
		{
			COL = !ft_strncmp(*line + COL, ".name", 5) ? 5 + COL : 8 + COL;
			write_name_or_comment(line, major, COL, 0);
		}
		else if (line && *line && **line != '\n')
			check_line(line, major, &token);
		ft_strdel(line);
		ROW++;
	}
	if (!token)
	{
		COL = 0;
		print_error(line, Syntax, "END at ", major);
	}
	validate_tokens(token, major);
	return (token);
}
