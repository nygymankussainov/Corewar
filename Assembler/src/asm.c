/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:35:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/01 21:03:55 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_usage(void)
{
	ft_printf("Usage: ./asm <file.s>\n");
}

int		main(int argc, char **argv)
{
	int		fd;
	t_major	*major;

	if (argc < 2)
		print_usage();
	if (!(major = (t_major *)ft_memalloc(sizeof(t_major))))
		exit(0);
	else if (!(fd = validation(argv[argc - 1], major)))
		exit(0);
	return (0);
}
