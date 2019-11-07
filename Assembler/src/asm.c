/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:35:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/07 12:51:34 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_usage(void)
{
	ft_printf("Usage: ./asm <your_champion.s>\n");
}

int		main(int argc, char **argv)
{
	t_major	*major;

	if (argc > 1)
	{
		if (!(major = (t_major *)ft_memalloc(sizeof(t_major))))
			ft_printf("%s\n", strerror(12));
		else if (!validation(argv[argc - 1], major))
			exit(1);
		free(major);
	}
	else
		print_usage();
	return (0);
}
