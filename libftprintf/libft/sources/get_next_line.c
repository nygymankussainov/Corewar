/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiant <egiant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:45:45 by egiant            #+#    #+#             */
/*   Updated: 2019/10/08 11:50:59 by egiant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		end_line(char **line, char **str, int flag)
{
	char	*temp;
	char	*temp2;

	if ((*str)[0] == '\0' && flag == 0)
	{
		*line = NULL;
		ft_memdel((void *)str);
		return (0);
	}
	else if ((temp2 = ft_strchr(*str, '\n')) != 0)
	{
		temp = *str;
		temp2[0] = '\0';
		*line = ft_strdup(temp);
		*str = ft_strdup(temp2 + 1);
		free(temp);
		return (1);
	}
	*line = *str;
	*str = NULL;
	if ((*line)[0] == '\0')
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char *str[10240];
	char		*temp;
	int			ret[2];

	if (fd < 0 || read(fd, NULL, 0) < 0 || !line || fd > 10240)
		return (-1);
	ret[1] = ((str[fd] == 0) ? 0 : 1);
	if (!(str[fd]))
		str[fd] = ft_strnew(0);
	if (ft_strchr(str[fd], '\n') == 0)
	{
		buf[0] = '\0';
		while (!(ft_strchr(buf, '\n')))
		{
			if ((ret[0] = read(fd, buf, BUFF_SIZE)) == 0)
				break ;
			buf[ret[0]] = '\0';
			temp = ft_strjoin(str[fd], buf);
			free(str[fd]);
			str[fd] = temp;
		}
	}
	return (end_line(line, &str[fd], ret[1]));
}
