/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_name_and_comment.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 11:27:57 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_line_after_quote(char *line, t_major *major)
{
	major->col++;
	while (line[major->col])
	{
		if (line[major->col] == '#')
			return (1);
		else if (ft_isascii(line[major->col]) && !iswhitesp(line[major->col]))
			return (0);
		major->col++;
	}
	return (1);
}

void	find_first_quote(char **line, t_major *major)
{
	while (line && *line && (*line)[major->col] && (*line)[major->col] != '"')
	{
		if (ft_isascii((*line)[major->col]) && !iswhitesp((*line)[major->col]))
			print_error(line, Lexical, "Missing quote at ", major);
		major->col++;
	}
	if ((*line)[major->col] == '\0')
		print_error(line, Lexical, "Missing quote at ", major);
	major->col++;
}

int		find_second_quote(char **line, t_major *major)
{
	while (line && *line && (*line)[major->col] && (*line)[major->col] != '"')
		major->col++;
	if (line && *line && (*line)[major->col] == '"')
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
			major->row++;
			major->col = 0;
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
	major->row = 1;
	while (get_next_line(major->fd, line, 0))
	{
		major->col = 0;
		if (line && *line && **line != '#' && **line != '.' &&
			**line != '\n' && ret < 2)
			print_error(line, Syntax, "Missing .name or .comment at ", major);
		else if (line && *line && (!ft_strncmp(*line, ".name", 5) ||
			!ft_strncmp(*line, ".comment", 8)))
		{
			major->col = !ft_strncmp(*line, ".name", 5) ? 5 : 8;
			if (!check_quotes(line, major))
				return (0);
			ret++;
		}
		if (ret == 2)
			return (1);
		ft_strdel(line);
		major->row++;
	}
	return (0);
}
