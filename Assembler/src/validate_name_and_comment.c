/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_name_and_comment.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/10 16:30:51 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_line_after_quote(char *line, t_major *major)
{
	COL++;
	while (line[COL])
	{
		if (line[COL] == '#')
			return (1);
		else if (ft_isascii(line[COL]) && !iswhitesp(line[COL]))
			return (0);
		COL++;
	}
	return (1);
}

void	find_first_quote(char **line, t_major *major)
{
	while (line && *line && (*line)[COL] && (*line)[COL] != '"')
	{
		if (ft_isascii((*line)[COL]) && !iswhitesp((*line)[COL]))
			print_error(line, Lexical, "Missing quote at ", major);
		COL++;
	}
	if ((*line)[COL] == '\0')
		print_error(line, Lexical, "Missing quote at ", major);
	COL++;
}

int		find_second_quote(char **line, t_major *major)
{
	while (line && *line && (*line)[COL] && (*line)[COL] != '"')
		COL++;
	if (line && *line && (*line)[COL] == '"')
	{
		if (check_line_after_quote(*line, major))
			return (1);
		else
			print_error(line, Lexical, "Invalid symbol after quote at ", major);
	}
	return (0);
}

int		check_quotes(char **line, t_major *major)
{
	find_first_quote(line, major);
	if (!find_second_quote(line, major))
	{
		ft_strdel(line);
		while (get_next_line(major->fd, line, 0))
		{
			ROW++;
			COL = 0;
			if (find_second_quote(line, major))
				return (1);
			ft_strdel(line);
		}
		print_error(line, Lexical, "Missing quote at ", major);
	}
	return (1);
}

int		validate_name_and_comment(char **line, t_major *major)
{
	int		ret;

	ret = 0;
	ROW = 1;
	while (get_next_line(major->fd, line, 0))
	{
		COL = **line != '\n' ? ft_skip_whitesp(*line, 0) : 0;
		if (line && *line && (*line)[COL] != '.' && (*line)[COL] != '\n' && ret < 2
		&& (*line)[COL] != COMMENT_CHAR && (*line)[COL] != ALT_COMMENT_CHAR)
			print_error(line, Syntax, "Missing .name or .comment at ", major);
		else if (line && *line && (!ft_strncmp(*line + COL, ".name", 5) ||
			!ft_strncmp(*line + COL, ".comment", 8)))
		{
			COL = !ft_strncmp(*line + COL, ".name", 5) ? 5 + COL : 8 + COL;
			if (!check_quotes(line, major))
				return (0);
			ret++;
		}
		if (ret == 2)
			return (1);
		ft_strdel(line);
		ROW++;
	}
	return (0);
}
