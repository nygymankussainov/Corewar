/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:35:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/11 19:10:01 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	assembler(char *filename)
{
	t_major	*major;
	t_token	*token;

	token = NULL;
	if (!(major = (t_major *)ft_memalloc(sizeof(t_major))))
	{
		ft_printf("%s\n", strerror(12));
		exit(12);
	}
	else if (!(token = validation(filename, major)))
		exit(1);
	compile_into_bytecode(token, major);
	free_structs(token, major);
}

int		main(int argc, char **argv)
{
	if (argc > 1)
		assembler(argv[argc - 1]);
	else
		ft_printf("Usage: ./asm <your_champion.s>\n");
	return (0);
}
