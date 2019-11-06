/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:50:12 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/14 13:52:35 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static t_gnl	v;

	v.b = 0;
	if (fd < 0 || read(fd, v.buff, 0) < 0 || !line)
		return (-1);
	while ((!v.c || (v.c && !ft_strchr(v.c, '\n')))
		&& (v.b = read(fd, v.buff, BUFF_SIZE)) > 0)
	{
		v.buff[v.b] = '\0';
		v.c = ft_strjoin(v.c, v.buff, 1, 0);
	}
	if (v.b == -1 || !v.c)
		return (v.b == -1 ? -1 : 0);
	if ((v.endl = (ft_strchr(v.c, '\n') > 0)))
		*line = ft_strsub(v.c, 0, ft_strchr(v.c, '\n') - v.c);
	else
		*line = ft_strdup(v.c);
	if (v.c)
		v.tmp = v.c;
	v.c = ft_strsub(v.c, (unsigned int)(ft_strlen(*line) + v.endl),
			(size_t)(ft_strlen(v.c) - (ft_strlen(*line) + v.endl)));
	ft_strdel(&v.tmp);
	return (!(!v.c && !ft_strlen(*line)));
}
