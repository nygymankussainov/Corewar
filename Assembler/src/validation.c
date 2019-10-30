/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/30 22:14:00 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		print_error(char *line, int i)
{
	if (i == 1)
	{
		putstrerr("Syntax error. ");
		putstrerr("Missing .name or .comment at the top of a file.\n");
		ft_strdel(&line);
	}
	return (0);
}

int		check_format(char *line, int i)
{
	char	*begin;

	begin = line;
	while (*line && *line != '"')
		line++;
	while (line && *line)
	{
		line++;
		if (*line == '"' && *(line + 1) == '\0')
			return (1);
		else if (*line == '"' && *(line + 1) != '\0')
			break ;
	}
	putstrerr("Lexical error. Must be covered in one pait of quotes on line ");
	ft_printf("%d.\n", i);
	ft_strdel(&begin);
	return (0);
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
			return (print_error(line, 1));
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

	if (!(fd = validate_file(file)) ||
		!validate_name_and_comment(fd, NULL))
		return (0);
	return (fd);
}
