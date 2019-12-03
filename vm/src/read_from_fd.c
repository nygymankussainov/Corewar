/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:46:53 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/12/03 19:16:14 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_type(int type)
{
	if (type == Magic_header)
		putstrerr("magic header");
	else if (type == Name)
		putstrerr("name");
	else if (type == Comment)
		putstrerr("comment");
	else if (type == Champ_code_size)
		putstrerr("champion code size");
	else
		putstrerr("EOF");
}

char	*read_from_fd(int fd, int size, int type, char *argv)
{
	char	*str;

	if (!(str = (char *)ft_memalloc(sizeof(char) * size + 1)))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	if (read(fd, str, size) <= 0)
	{
		putstrerr("Couldn't read ");
		print_type(type);
		putstrerr(" from ");
		putstrerr(argv);
		putstrerr("\n");
		return (NULL);
	}
	return (str);
}
