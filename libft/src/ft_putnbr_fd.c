/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:39:52 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/04/19 20:12:57 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_2(long ln, int fd_2)
{
	if (ln < 0)
	{
		ft_putchar_fd('-', fd_2);
		ft_putnbr_fd_2((ln * -1), fd_2);
	}
	else if (ln > 9)
	{
		ft_putnbr_fd_2(ln / 10, fd_2);
		ft_putnbr_fd_2(ln % 10, fd_2);
	}
	else
		ft_putchar_fd(ln + 48, fd_2);
}

void		ft_putnbr_fd(int n, int fd)
{
	long	j;

	j = n;
	ft_putnbr_fd_2(j, fd);
}
