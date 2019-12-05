/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_name_and_comment.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 18:01:24 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		validate_line(char **line, t_major *major, bool name, bool comment)
{
	COL = **line != '\n' ? ft_skip_whitesp(*line, 0) : 0;
	if (line && *line && (*line)[COL] != '.' && (*line)[COL] != '\n'
	&& (*line)[COL] != COMMENT_CHAR && (*line)[COL] != ALT_COMMENT_CHAR
	&& (!name || !comment))
		return (0);
	return (1);
}

int		validate_name_and_comment(char **line, t_major *major)
{
	bool	name;
	bool	comment;

	ROW = 1;
	name = 0;
	comment = 0;
	while (get_next_line(major->fd, line, 0))
	{
		if (!validate_line(line, major, name, comment))
			print_error(line, Syntax, "Missing .name or .comment at ", major);
		else if (line && *line && (!ft_strncmp(*line + COL, ".name", 5) ||
			!ft_strncmp(*line + COL, ".comment", 8)))
		{
			COL = !ft_strncmp(*line + COL, ".name", 5) ? 5 + COL : 8 + COL;
			name = COL < 8 ? 1 : name;
			comment = COL >= 8 ? 1 : comment;
			if (!check_quotes(line, major))
				return (0);
		}
		if (name && comment)
			return (1);
		ft_strdel(line);
		ROW++;
	}
	return (0);
}
