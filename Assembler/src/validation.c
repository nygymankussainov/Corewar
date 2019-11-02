/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:07:38 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/02 21:39:46 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		validation(char *file, t_major *major)
{
	char	*line;

	line = NULL;
	if (!(major->fd = validate_file(file)) ||
		!validate_name_and_comment(&line, major))
		return (0);
	ft_strdel(&line);
	get_next_line(major->fd, &line, 1);
	lseek(major->fd, 0, SEEK_SET);
	tokenization(&line, major);
	return (1);
}
