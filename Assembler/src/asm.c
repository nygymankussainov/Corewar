/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:35:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/30 21:42:34 by vhazelnu         ###   ########.fr       */
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

	if (argc < 2)
		print_usage();
	else if (!(fd = validation(argv[argc - 1])))
		exit(0);
	return (0);
}
