/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/01 22:28:28 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_error(char **line, int type, char *message, t_major *major)
{
	if (type == Syntax)
		putstrerr("Syntax error. ");
	else if (type == Lexical)
		putstrerr("Lexical error. ");
	putstrerr(message);
	ft_printf("[%d:%d].\n", major->row, major->col);
	ft_strdel(line);
	exit(type);
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
		if ((*line)[major->col + 1] == '\0')
			return (1);
		else
			print_error(line, Lexical, "Invalid symbol after quote at ", major);
	}
	return (0);
}

int		check_quotes(int fd, char **line, t_major *major)
{
	find_first_quote(line, major);
	if (!find_second_quote(line, major))
	{
		ft_strdel(line);
		while (get_next_line(fd, line))
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

int		validate_name_and_comment(int fd, char *line, t_major *major)
{
	int		ret;

	ret = 0;
	major->row = 1;
	while (get_next_line(fd, &line))
	{
		if (line && line[0] != '#' && line[0] != '.' && ret < 2)
		{
			major->row--;
			print_error(&line, Syntax, "Missing .name or .comment at ", major);
		}
		if (line && (!ft_strncmp(line, ".name", 5) ||
			!ft_strncmp(line, ".comment", 8)))
		{
			major->col = !ft_strncmp(line, ".name", 5) ? 5 : 8;
			if (!check_quotes(fd, &line, major))
				return (0);
			ret++;
		}
		if (ret == 2)
		{
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&line);
		major->row++;
	}
	return (0);
}

int		validation(char *file, t_major *major)
{
	int		fd;
	char	*line;

	line = NULL;
	if (!(fd = validate_file(file)) ||
		!validate_name_and_comment(fd, line, major))
	{
		if (fd > 0)
			while (get_next_line(fd, &line))
				ft_strdel(&line);
		return (0);
	}
	return (fd);
}
