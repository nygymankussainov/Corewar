/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/01 17:07:25 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_error(char *line, int type, int i, int j)
{
	if (type == 1)
	{
		putstrerr("Syntax error. Missing .name or .comment on line ");
		ft_printf("%d.\n", i);
	}
	else if (type == 2)
	{
		putstrerr("Lexical error. Missing quote at ");
		ft_printf("[%d:%d].\n", i, j);
	}
	else if (type == 3)
	{
		putstrerr("Lexical error. Extra quote at ");
		ft_printf("[%d:%d].\n", i, j);
	}
	ft_strdel(&line);
	return (0);
}

int		check_format(char *line, int i)
{
	int		len;
	int		j;

	len = ft_strlen(line);
	if (line[len - 1] != '"')
		return (print_error(line, 2, i, len));
	j = !ft_strncmp(line, ".name", 5) ? 5 : 8;
	if (ft_isalnum(line[j]))
		return (print_error(line, 2, i, j));
	while (line[j] && line[j] != '"')
		j++;
	if ((ft_isascii(line[j - 1]) && !iswhitesp(line[j - 1])) ||
		len - 1 - j++ == 0)
	{
		j = !ft_strncmp(line, ".name", 5) ? 5 : 8;
		while (!ft_isalnum(line[j]))
			j++;
		return (print_error(line, 2, i, j));
	}
	while (line[j] && line[j] != '"')
		j++;
	if (len - 1 - j != 0)
		return (print_error(line, 3, i, j));
	return (1);
}

int		validate_name_and_comment(int fd, char *line)
{
	int		ret;
	int		i;

	ret = 0;
	i = 1;
	while (get_next_line(fd, &line))
	{
		if (line && line[0] != '#' && line[0] != '.' && ret < 2)
			return (print_error(line, 1, i - 1, 0));
		if (line && (!ft_strncmp(line, ".name", 5) ||
			!ft_strncmp(line, ".comment", 8)))
		{
			if (!check_format(line, i))
				return (0);
			ret++;
		}
		if (ret == 2)
		{
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&line);
		i++;
	}
	return (0);
}

int		validation(char *file)
{
	int		fd;
	char	*line;

	line = NULL;
	if (!(fd = validate_file(file)) ||
		!validate_name_and_comment(fd, line))
	{
		if (fd > 0)
			while (get_next_line(fd, &line))
				ft_strdel(&line);
		return (0);
	}
	return (fd);
}
