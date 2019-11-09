/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:35:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/11/09 18:54:07 by vhazelnu         ###   ########.fr       */
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
	t_token	*token;
	t_token	*tmp;

	token = NULL;
	if (argc > 1)
	{
		if (!(major = (t_major *)ft_memalloc(sizeof(t_major))))
		{
			ft_printf("%s\n", strerror(12));
			exit(12);
		}
		else if (!(token = validation(argv[argc - 1], major)))
			exit(1);
		convert_in_byte_code(token, major);
		while (token)
		{
			tmp = token->next;
			ft_strdel(&token->name);
			free(token);
			token = tmp;
		}
		token = NULL;
		free(major);
		major = NULL;
	}
	else
		print_usage();
	return (0);
}
