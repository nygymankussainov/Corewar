/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:50:12 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 11:25:56 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		error_occured(char **str)
{
	if (!str || !*str)
		return (0);
	ft_strdel(str);
	return (0);
}

int		get_next_line(const int fd, char **line, bool err)
{
	static t_gnl	gnl;

	gnl.byte = 0;
	if (err)
		return (error_occured(&gnl.str));
	if (fd < 0 || read(fd, gnl.buff, 0) < 0 || !line)
		return (-1);
	while ((!gnl.str || (gnl.str && !ft_strchr(gnl.str, '\n')))
		&& (gnl.byte = read(fd, gnl.buff, BUFF_SIZE)) > 0)
	{
		gnl.buff[gnl.byte] = '\0';
		gnl.str = ft_strjoin(gnl.str, gnl.buff, 1, 0);
	}
	if (gnl.byte == -1 || !gnl.str)
		return (gnl.byte == -1 ? -1 : 0);
	if (ft_strchr(gnl.str, '\n') > 0)
		*line = ft_strsub(gnl.str, 0, ft_strchr(gnl.str, '\n') - gnl.str + 1);
	else
		*line = ft_strdup(gnl.str);
	if (gnl.str)
		gnl.tmp = gnl.str;
	gnl.str = ft_strsub(gnl.str, (unsigned int)ft_strlen(*line),
			(size_t)(ft_strlen(gnl.str) - ft_strlen(*line)));
	ft_strdel(&gnl.tmp);
	return (!(!gnl.str && !ft_strlen(*line)));
}
