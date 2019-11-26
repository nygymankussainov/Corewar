/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:03:34 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/26 17:19:44 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		isplayer(char *str)
{
	if (ft_strstr(str, ".cor"))
		return (1);
	return (0);
}

int		count_players(int argc, char **argv)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (i < argc)
	{
		if (isplayer(argv[i]))
			count++;
		i++;
	}
	return (count);
}

void	print_usage(void)
{
	ft_printf("%s\n", "Usage: ./corewar <champion.cor>");
}

int		main(int argc, char **argv)
{
	int		nb;

	if (argc < 2)
		print_usage();
	nb = count_players(argc, argv);
	if (nb > MAX_PLAYERS)
		putstrerr("Too many champions\n");
	else if (validation(argc, argv, nb))
	{
		return (1);
	}
	return (0);
}
